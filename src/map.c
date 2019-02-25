#include <gb/gb.h>

#include "./define.h"
#include "./map.h"

UINT16 _map_x;
UINT16 _map_y;
UINT8* _map_bg;
UINT16 _map_bg_width;
UINT16 _map_bg_height;
UINT8 _map_bg_x;
UINT8 _map_bg_y;

void map_bg_set(UINT8* map, UINT16 width, UINT16 height) {
    _map_x = 0;
    _map_y = 0;
    _map_bg_x = 0;
    _map_bg_y = 0;
    _map_bg = map;
    _map_bg_width = width;
    _map_bg_height = height;
}

void map_bg_load_chunk(UINT16 sx, UINT16 sy, UINT8 dx, UINT8 dy, UINT8 w, UINT8 h) {
    UINT8 y;
    UINT16 offset;
    UINT8 *lptr = NULL;

    if (dx + w > GB_BG_WIDTH) {
        map_bg_load_chunk(
                sx,
                sy,
                dx,
                dy,
                GB_BG_WIDTH - dx,
                h);
        map_bg_load_chunk(
                sx + (GB_BG_WIDTH - dx),
                sy,
                0,
                dy,
                w - (GB_BG_WIDTH - dx),
                h);
    } else {
        for (y = 0 ; y < h ; y++) {
            offset = (sy + y) * _map_bg_width + sx;
            lptr = _map_bg + offset;
            set_bkg_tiles(dx, (dy + y) % GB_BG_HEIGHT, w, 1, lptr);
        }
    }
}

// Returned coordinates represents the center of the screen
void map_get_coord(UINT16* x, UINT16* y) {
    *x = _map_x + 9;
    *y = _map_y + 8;
}

// Given coordinates represents the center of the screen
void map_goto(UINT16 x, UINT16 y) {
    _map_x = x - 9;
    _map_y = y - 8;
    _map_bg_x = 8;
    _map_bg_y = 8;
    move_bkg(8, 8);
    map_bg_load_chunk(_map_x - 1, _map_y - 1, 0, 0, 22, 20);
}

// WARN:
//    -1 <= dx <= 1
//    -1 <= dy <= 1
void map_scroll(INT8 dx, INT8 dy) {
    // Update coords (> 0)
    if (dx == 1) _map_bg_x += 1;
    if (dy == 1) _map_bg_y += 1;
    // Load new tiles if necessary
    if (dx && !(_map_bg_x % 8)) {
        if (dx == 1) {
            _map_x += 1;
            map_bg_load_chunk(
                    _map_x + GB_SCREEN_WIDTH,
                    _map_y - 1,
                    ((UINT8)((_map_bg_x/8) + GB_SCREEN_WIDTH)) % GB_BG_WIDTH,
                    ((UINT8)(_map_bg_y/8 - 1)) % GB_BG_HEIGHT,
                    1,
                    GB_SCREEN_HEIGHT + 2);
        } else {
            _map_x -= 1;
            map_bg_load_chunk(
                    _map_x,
                    _map_y - 1,
                    ((UINT8)(_map_bg_x/8 - 1)) % GB_BG_WIDTH,
                    ((UINT8)(_map_bg_y/8 - 1)) % GB_BG_HEIGHT,
                    1,
                    GB_SCREEN_HEIGHT + 2);
        }
    }
    if (dy && !(_map_bg_y % 8)) {
        if (dy == 1) {
            _map_y += 1;
            map_bg_load_chunk(
                    _map_x - 1,
                    _map_y + GB_SCREEN_HEIGHT,
                    ((UINT8)(_map_bg_x/8 - 1)) % GB_BG_WIDTH,
                    ((UINT8)(_map_bg_y/8 + GB_SCREEN_HEIGHT)) % GB_BG_HEIGHT,
                    GB_SCREEN_WIDTH + 2,
                    1);
        } else {
            _map_y -= 1;
            map_bg_load_chunk(
                    _map_x - 1,
                    _map_y,
                    ((UINT8)(_map_bg_x/8 - 1)) % GB_BG_WIDTH,
                    ((UINT8)(_map_bg_y/8 - 1)) % GB_BG_HEIGHT,
                    GB_SCREEN_WIDTH + 2,
                    1);
        }
    }
    // Update coords (<0)
    if (dx == -1) _map_bg_x -= 1;
    if (dy == -1) _map_bg_y -= 1;
    // Scroll
    scroll_bkg(dx, dy);
}

UINT8 map_cell_is_walkable(UINT16 x, UINT16 y) {
    UINT16 tile_offset = y * _map_bg_width + x;
    UINT8 tile_id = _map_bg[tile_offset];
    if (tile_id < MAP_WALKABLE_THRESHOLD) {
        return TRUE;
    }
    return FALSE;
}
