#ifndef _GAME_H
#define _GAME_H

#include <types.h>

#include "./player.h"

struct GameState {
    UINT8 dpad_mask;
    UINT8 player_has_sword;
    Player* player;
};

typedef struct GameState GameState;

void game_init();
void game_main();
void game_end();

#endif
