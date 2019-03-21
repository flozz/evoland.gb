#include <stdlib.h>
#include <gb/gb.h>

#include "./define.h"
#include "./map.h"
#include "./bgb_debug.h"

/*UINT8 MAP_ACTIVATED_CELL_PATCH[] = {0x0E, 0x0F, 0x1E, 0x1F};  // FIXME debug*/
UINT8 MAP_ACTIVATED_CELL_PATCH[] = {0x00, 0x01, 0x10, 0x11};

Map* map_new(UINT8* bg_map, UINT8 bg_map_width, UINT8 bg_map_height) {
    Map* map = malloc(sizeof(Map));
    UINT16 patch_map_length = sizeof(UINT8) * bg_map_width * bg_map_height / 16;

    if (map == NULL) {
        return NULL;
    }

    map->x = 0;
    map->y = 0;
    map->bg_map = bg_map;
    map->bg_map_width = bg_map_width;
    map->bg_map_height = bg_map_height;
    map->_bg_layer_x = 0;
    map->_bg_layer_y = 0;
    map->_bg_map_patch = malloc(patch_map_length);

    while (patch_map_length) {
        patch_map_length -= 1;
        map->_bg_map_patch[patch_map_length] = 0x00;
    }

    return map;
}

inline void map_cell_patch(Map* map, UINT8 x, UINT8 y) {
    UINT8 screen_x;
    UINT8 screen_y;
    //                                 map->_bg_layer_x / 8
    screen_x = (((UINT8)(x - map->x + (map->_bg_layer_x >> 3))) % GB_BG_WIDTH) & 0xFE;
    //                                 map->_bg_layer_y / 8
    screen_y = (((UINT8)(y - map->y + (map->_bg_layer_y >> 3))) % GB_BG_HEIGHT) & 0xFE;
    set_bkg_tiles(screen_x, screen_y, 2, 2, MAP_ACTIVATED_CELL_PATCH);
}

inline UINT8 map_cell_is_activated(Map* map, UINT8 x, UINT8 y) {
    //         =  y/2 * map->bg_map_width/2 + x/2
    UINT16 tmp = (y >> 1) * (map->bg_map_width >> 1) + (x >> 1);
    //     map->_bg_map_patch[tmp/8]               (tmp % 8)
    return map->_bg_map_patch[tmp >> 3] & (0x01 << (tmp & 7));
}

void map_cell_set_activated(Map* map, UINT8 x, UINT8 y) {
    UINT16 map_byte_offset;
    UINT8 map_byte;
    UINT8 map_bit_mask;
    map_byte_offset = (y/2 * map->bg_map_width/2 + x/2) / 8;
    map_byte = map->_bg_map_patch[map_byte_offset];
    map_bit_mask = 0x01 << ((y/2 * map->bg_map_width/2 + x/2) % 8);
    map->_bg_map_patch[map_byte_offset] = map_byte | map_bit_mask;
    // Also replace visible tiles
    map_cell_patch(map, x, y);
}

inline void _map_bg_load_chunk(
        Map* map,
        UINT8 sx,
        UINT8 sy,
        UINT8 dx,
        UINT8 dy,
        UINT8 w,
        UINT8 h) {
    UINT8 y;
    UINT8 x;
    UINT16 offset;
    UINT8* lptr = NULL;
    for (y = 0 ; y != h ; y++) {
        offset = (sy + y) * map->bg_map_width + sx;
        lptr = map->bg_map + offset;
        set_bkg_tiles(dx, (dy + y) % GB_BG_HEIGHT, w, 1, lptr);
        //  y % 2
        if (y & 1 == 0) {
            continue;
        }
        for (x = 0 ; x != w ; x += 2) {
            if (map_cell_is_activated(map, sx + x, sy + y)) {
                map_cell_patch(map, sx + x, sy + y);
            }
        }
    }
}

void map_bg_load_chunk(
        Map* map,
        UINT8 sx,
        UINT8 sy,
        UINT8 dx,
        UINT8 dy,
        UINT8 w,
        UINT8 h) {

    if (dx + w > GB_BG_WIDTH) {
        _map_bg_load_chunk(
                map,
                sx,
                sy,
                dx,
                dy,
                GB_BG_WIDTH - dx,
                h);
        _map_bg_load_chunk(
                map,
                sx + (GB_BG_WIDTH - dx),
                sy,
                0,
                dy,
                w - (GB_BG_WIDTH - dx),
                h);
    } else {
        _map_bg_load_chunk(map, sx, sy, dx, dy, w, h);
    }
}

// Given coordinates represents the center of the screen (FIXME)
void map_goto(Map* map, UINT8 x, UINT8 y) {
    map->x = x - GB_SCREEN_CENTER_X;
    map->y = y - GB_SCREEN_CENTER_Y;
    map->_bg_layer_x = 0;
    map->_bg_layer_y = 0;
    move_bkg(0, 0);
    map_bg_load_chunk(map, map->x, map->y, 0, 0, 20, 18);
}

// WARN:
//    -1 <= dx <= 1
//    -1 <= dy <= 1
void map_scroll(Map* map, INT8 dx, INT8 dy) {

    //              map->_bg_layer_x % 16
    if (dx == 1 && (map->_bg_layer_x & 15) == 0) {
        map_bg_load_chunk(
                map,
                map->x + GB_SCREEN_WIDTH,
                map->y,
                // map->_bg_layer_x / 8
                ((map->_bg_layer_x >> 3) + GB_SCREEN_WIDTH) % GB_BG_WIDTH,
                // map->_bg_layer_y / 8
                (map->_bg_layer_y >> 3) % GB_BG_HEIGHT,
                2,
                GB_SCREEN_HEIGHT);
        map->x += 2;
    //                      map->_bg_layer_x % 16
    } else if (dx == -1 && (map->_bg_layer_x & 15) == 0) {
        map_bg_load_chunk(
                map,
                map->x - 2,
                map->y,
                //              map->_bg_layer_x / 8
                (GB_BG_WIDTH + (map->_bg_layer_x >> 3) - 2) % GB_BG_WIDTH,
                // map->_bg_layer_y / 8
                (map->_bg_layer_y >> 3) % GB_BG_HEIGHT,
                2,
                GB_SCREEN_HEIGHT);
        map->x -= 2;
    }

    //              map->_bg_layer_y % 16
    if (dy == 1 && (map->_bg_layer_y & 15) == 0) {
        map_bg_load_chunk(
                map,
                map->x,
                map->y + GB_SCREEN_HEIGHT,
                // map->_bg_layer_x / 8
                (map->_bg_layer_x >> 3) % GB_BG_WIDTH,
                // map->_bg_layer_y / 8
                ((map->_bg_layer_y >> 3) + GB_SCREEN_HEIGHT) % GB_BG_HEIGHT,
                GB_SCREEN_WIDTH,
                2);
        map->y += 2;
    //                      map->_bg_layer_y % 16
    } else if (dy == -1 && (map->_bg_layer_y & 15) == 0) {
        map_bg_load_chunk(
                map,
                map->x,
                map->y - 2,
                // map->_bg_layer_x / 8
                (map->_bg_layer_x >> 3) % GB_BG_WIDTH,
                //               map->_bg_layer_y / 8
                (GB_BG_HEIGHT + (map->_bg_layer_y >> 3) - 2) % GB_BG_HEIGHT,
                GB_SCREEN_WIDTH,
                2);
        map->y -= 2;
    }

    map->_bg_layer_x += dx;
    map->_bg_layer_y += dy;

    // Scroll
    scroll_bkg(dx, dy);
}

UINT8 map_cell_is_walkable(Map* map, UINT8 x, UINT8 y) {
    UINT16 tile_offset;
    UINT8 tile_id;
    // Check BG Map
    tile_offset = y * map->bg_map_width + x;
    tile_id = map->bg_map[tile_offset];
    if (tile_id < MAP_WALKABLE_THRESHOLD) {
        return TRUE;
    }
    // Check Patch map
    return map_cell_is_activated(map, x, y);
}

UINT8 map_cell_is_chest(Map* map, UINT8 x, UINT8 y) {
    UINT16 tile_offset;
    UINT8 tile_id;
    tile_offset = y * map->bg_map_width + x;
    tile_id = map->bg_map[tile_offset];
    return tile_id == MAP_OBJECT_CHEST;
}

UINT8 map_cell_is_bush(Map* map, UINT8 x, UINT8 y) {
    UINT16 tile_offset;
    UINT8 tile_id;
    tile_offset = y * map->bg_map_width + x;
    tile_id = map->bg_map[tile_offset];
    return tile_id == MAP_OBJECT_BUSH;
}

void map_free(Map* map) {
    // TODO
}
