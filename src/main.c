#include <gb/gb.h>

#include "./define.h"
#include "./map.h"
#include "./sprite16.h"
#include "./gassets/background.tileset.h"
#include "./gassets/background.tilemap.h"
#include "./gassets/sprites.tileset.h"

void main(void) {
    INT8 dx;
    INT8 dy;
    UINT8 keys;

    set_bkg_data(0, BG_TILESET_TILE_COUNT, BG_TILESET);
    set_sprite_data(0, SPRITES_TILE_COUNT, SPRITES);

    map_bg_set(BG_TILEMAP, BG_TILEMAP_WIDTH, BG_TILEMAP_HEIGHT);

    map_goto(24, 46);

    SHOW_BKG;

    SPRITES_8x16;
    SHOW_SPRITES;

    OBP0_REG = 0xE0;  // FIXME
    sprite16_new(0, 0, 80, 80);  // FIXME

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

