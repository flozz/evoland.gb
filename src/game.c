#include "./define.h"
#include "./palette.h"
#include "./map.h"
#include "./player.h"
#include "./sprite16.h"
#include "./gassets/background.tileset.h"
#include "./gassets/background.tilemap.h"
#include "./gassets/sprites.tileset.h"

Player* _game_player;
Map* _game_map;

void game_init() {
    SHOW_BKG;
    SPRITES_8x16;
    SHOW_SPRITES;

    palette_set_obp0(PALETTE_WHITE, PALETTE_WHITE, PALETTE_GRAY, PALETTE_BLACK);

    set_bkg_data(0, BG_TILESET_TILE_COUNT, BG_TILESET);
    set_sprite_data(0, SPRITES_TILE_COUNT, SPRITES);

    _game_map = map_new(BG_TILEMAP, BG_TILEMAP_WIDTH, BG_TILEMAP_HEIGHT);
    map_goto(_game_map, 24, 46);

    _game_player = player_new();
}

void game_main() {
    INT8 dx;
    INT8 dy;
    UINT8 keys;

    while (TRUE) {
        dx = 0;
        dy = 0;
        keys = joypad();

        if (keys & J_UP) dy -= 1;
        if (keys & J_DOWN) dy += 1;
        if (keys & J_LEFT) dx -= 1;
        if (keys & J_RIGHT) dx += 1;

        if (dx || dy) {
            player_walk_to_cell(_game_player, _game_map, dx, dy);
        }

        player_update(_game_player, _game_map);
        sprite16anim_update();
        wait_vbl_done();
    }
}

void game_end() {
    // TODO
}
