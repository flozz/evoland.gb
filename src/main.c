#include <gb/gb.h>

#include "./define.h"
#include "./background.tileset.h"
#include "./background.tilemap.h"

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

    for (y = 0 ; y < h ; y++) {
        offset = (sy + y) * _map_bg_width + sx;
        lptr = _map_bg + offset;
        set_bkg_tiles(dx, dy + y, w, 1, lptr);
    }
}

void map_goto(UINT16 x, UINT16 y) {
    _map_x = x - 9;
    _map_y = y - 8;
    _map_bg_x = 8;
    _map_bg_y = 8;
    move_bkg(8, 8);
    map_bg_load_chunk(_map_x - 1, _map_y - 1, 0, 0, 22, 20);
}

void map_scroll(INT8 dx, INT8 dy) {
    // Update coords
    _map_bg_x += dx;
    _map_bg_y += dy;
    // Load new tiles if necessary
    if (dx && !(_map_bg_x % 8)) {
        /*if (dx > 0) {*/
        if (dx == 1) {
            _map_x += 1;
            map_bg_load_chunk(
                    _map_x + 20,
                    _map_y - 1,
                    (_map_bg_x/8 + 20) % 32,
                    (_map_bg_y/8 - 1) % 32,
                    1,
                    20);
        } else {
            _map_x -= 1;
            map_bg_load_chunk(
                    _map_x,
                    _map_y - 1,
                    (_map_bg_x/8 - 1) % 32,
                    (_map_bg_y/8 - 1) % 32,
                    1,
                    20);
        }
    }
    if (dy && !(_map_bg_y % 8)) {
        /*if (dy > 0) {*/
        if (dy == 1) {
            _map_y += 1;
            map_bg_load_chunk(
                    _map_x - 1,
                    _map_y + 18,
                    (_map_bg_x/8 - 1) % 32,
                    (_map_bg_y/8 + 18) % 32,
                    22,
                    1);
        } else {
            _map_y -= 1;
            map_bg_load_chunk(
                    _map_x - 1,
                    _map_y,
                    (_map_bg_x/8 - 1) % 32,
                    (_map_bg_y/8 - 1) % 32,
                    22,
                    1);
        }
    }
    // Scroll
    scroll_bkg(dx, dy);
}

void main(void) {
    INT8 dx;
    INT8 dy;
    UINT8 keys;

    set_bkg_data(0, BG_TILESET_TILE_COUNT, BG_TILESET);
    map_bg_set(BG_TILEMAP, BG_TILEMAP_WIDTH, BG_TILEMAP_HEIGHT);
    map_goto(24, 46);
    SHOW_BKG;

    while (TRUE) {
        dx = 0;
        dy = 0;
        keys = joypad();

        if (keys & J_UP) dy -= 1;
        if (keys & J_DOWN) dy += 1;
        if (keys & J_LEFT) dx -= 1;
        if (keys & J_RIGHT) dx += 1;

        if (dx || dy) {
            map_scroll(dx, dy);
        }

        wait_vbl_done();
    }
}

