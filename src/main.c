#include <gb/gb.h>

#include "./define.h"
#include "./palette.h"
#include "./map.h"
#include "./player.h"
#include "./sprite16-anim.h"
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

    map_goto(24, 46);  // FIXME

    SHOW_BKG;

    SPRITES_8x16;
    SHOW_SPRITES;

    palette_set_obp0(PALETTE_WHITE, PALETTE_WHITE, PALETTE_GRAY, PALETTE_BLACK);

    player_init();
    sprite16anim_init();

    while (TRUE) {
        dx = 0;
        dy = 0;
        keys = joypad();

        if (keys & J_UP) dy -= 1;
        if (keys & J_DOWN) dy += 1;
        if (keys & J_LEFT) dx -= 1;
        if (keys & J_RIGHT) dx += 1;

        if (dx || dy) {
            player_walk_to_cell(dx, dy);
        }

        player_loop();
        sprite16anim_loop();
        wait_vbl_done();
    }
}

