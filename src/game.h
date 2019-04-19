#ifndef _GAME_H
#define _GAME_H

#include <types.h>

#include "./player.h"
#include "./map.h"

#define GAME_ORIG_X 24
#define GAME_ORIG_Y 46

struct GameState {
    UINT8 dpad_mask;
    UINT8 player_has_sword;
    Map* map;
    Player* player;
};

typedef struct GameState GameState;

void game_init();
void game_mask_y();
void game_main();
void game_end();

#endif
