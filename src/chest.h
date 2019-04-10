#ifndef _CHEST_H
#define _CHEST_H

#include "./game.h"

UINT8 chest_get_id(UINT8 x, UINT8 y);
void chest_activate(GameState* game_state, UINT8 chest_id);

#endif
