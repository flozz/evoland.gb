#include <gb/gb.h>

#include "./define.h"
#include "./game.h"
#include "./map.h"
#include "./text.h"
#include "./locales/messages.h"
#include "./objects/chests.objects.h"


UINT8 chest_get_id(UINT8 x, UINT8 y) {
    UINT8 i;
    for (i = 0 ; i < CHESTS_COUNT ; i += 1) {
        if (CHESTS[i * 3] != x) {
            continue;
        }
        if (CHESTS[i * 3 + 1] != y) {
            continue;
        }
        return CHESTS[i * 3 + 2];
    }
    return 255;
}

void chest_activate(GameState* game_state, UINT8 chest_id) {
    UINT8 i;
    switch(chest_id) {
        case 0:
            text_show_message(MSG_1, 4);
            game_state->dpad_mask |= J_LEFT;
            break;
        case 1:
            for (i = 1 ; i <= 8 ; i += 1) {
                map_bg_load_chunk(
                    game_state->map,
                    GAME_ORIG_X - 8,
                    GAME_ORIG_Y - i,
                    0,
                    GB_SCREEN_CENTER_Y - i,
                    GB_SCREEN_WIDTH,
                    1);
                map_bg_load_chunk(
                    game_state->map,
                    GAME_ORIG_X - GB_SCREEN_CENTER_X,
                    GAME_ORIG_Y + i + 1,
                    0,
                    GB_SCREEN_CENTER_Y + i + 1,
                    GB_SCREEN_WIDTH,
                    1);
                wait_vbl_done();
                wait_vbl_done();
            }
            text_show_message(MSG_2, 4);
            game_state->dpad_mask |= J_UP | J_DOWN;
            break;
        case 2:
            text_show_message(MSG_3, 4);
            break;
        case 3:
            text_show_message(MSG_4, 4);
            break;
        case 4:
            text_show_message(MSG_5, 4);
            game_state->player->smooth_scrolling = TRUE;
            break;
        case 5:
            text_show_message(MSG_6, 4);
            game_state->player_has_sword = TRUE;
            break;
        default:
            text_show_message("...\0", 4);  // FIXME
    }
}
