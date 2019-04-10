#include <stdlib.h>

#include <gb/gb.h>

#include "./game.h"
#include "./define.h"
#include "./palette.h"
#include "./map.h"
#include "./player.h"
#include "./sprite16.h"
#include "./text.h"
#include "./bgb_debug.h"
#include "./fx.h"
#include "./chest.h"
#include "./locales/messages.h"
#include "./gassets/background.tileset.h"
#include "./gassets/background.tilemap.h"
#include "./gassets/sprites.tileset.h"

Player* _game_player;
Map* _game_map;
GameState* _game_state;

void game_init() {
    SPRITES_8x16;

    palette_set_obp0(PALETTE_WHITE, PALETTE_WHITE, PALETTE_GRAY, PALETTE_BLACK);

    set_bkg_data(0, BG_TILESET_TILE_COUNT, BG_TILESET);
    set_sprite_data(0, SPRITES_TILE_COUNT, SPRITES);
    text_load_font();

    _game_map = map_new(BG_TILEMAP, BG_TILEMAP_WIDTH, BG_TILEMAP_HEIGHT);
    map_goto(_game_map, 24, 46);

    _game_player = player_new();

    _game_state = malloc(sizeof(GameState));
    _game_state->dpad_mask = 0x00;
    _game_state->player_has_sword = FALSE;

    SHOW_SPRITES;
}

void game_main() {
    INT8 dx;
    INT8 dy;
    UINT8 next_cell_x;
    UINT8 next_cell_y;
    UINT8 keys;
    UINT8 last_keys = 0x00;

    fx_bg_fade_in();

    _game_state->dpad_mask = J_RIGHT;
    text_show_message(MSG_0, 4);

    while (TRUE) {
        dx = 0;
        dy = 0;
        keys = joypad();

        if (keys & J_UP & _game_state->dpad_mask) dy -= 1;
        if (keys & J_DOWN & _game_state->dpad_mask) dy += 1;
        if (keys & J_LEFT & _game_state->dpad_mask) dx -= 1;
        if (keys & J_RIGHT & _game_state->dpad_mask) dx += 1;

        if (dx || dy) {
            next_cell_x = _game_map->x + GB_SCREEN_CENTER_X + dx * 2;
            next_cell_y = _game_map->y + GB_SCREEN_CENTER_Y + dy * 2;
        } else {
            next_cell_x = _game_map->x + GB_SCREEN_CENTER_X + _game_player->dx * 2;
            next_cell_y = _game_map->y + GB_SCREEN_CENTER_Y + _game_player->dy * 2;
        }

        //  (_game_map->_bg_layer_x % 16)         (_game_map->_bg_layer_y % 16)
        if ((_game_map->_bg_layer_x & 15) == 0 && (_game_map->_bg_layer_y & 15) == 0) {
            // Cut bushes
            if (keys & J_A && !(last_keys & J_A) && _game_state->player_has_sword && map_cell_is_bush(_game_map, next_cell_x, next_cell_y)) {
                map_cell_set_activated(_game_map, next_cell_x, next_cell_y);
            }

            if (keys & GB_J_DPAD & _game_state->dpad_mask && map_cell_is_chest(_game_map, next_cell_x, next_cell_y)) {
                map_cell_set_activated(_game_map, next_cell_x, next_cell_y);
                chest_activate(_game_state, chest_get_id(next_cell_x, next_cell_y));

                // cancel hit / walk actions
                wait_vbl_done();
                continue;
            }
        }

        if (keys & J_A && !(last_keys & J_A) && _game_state->player_has_sword) {
            player_hit(_game_player);
        }

        if (dx || dy) {
            player_walk_to_cell(_game_player, _game_map, dx, dy);
        }

        player_update(_game_player, _game_map);
        sprite16anim_update();

        last_keys = keys;

        wait_vbl_done();
    }
}

void game_end() {
    // TODO
}
