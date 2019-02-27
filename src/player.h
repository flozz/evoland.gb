#ifndef _PLAYER_H
#define _PLAYER_H

#include "./sprite16.h"
#include "./sprite16-anim.h"

struct Player {
    Sprite16* sprite;
    Sprite16Anim* anim_down;
    Sprite16Anim* anim_up;
    Sprite16Anim* anim_right;
    Sprite16Anim* anim_left;
    UINT8 _walk_to_dx;
    UINT8 _walk_to_dy;
    UINT8 _walk_to_count;
    UINT8 _is_walking;
    Sprite16Anim* _anim_current;
};

typedef struct Player Player;

void player_init();
Player* player_new();
void player_walk_to_cell(INT8 dx, INT8 dy);
void player_loop();
void _player_free(Player* player);

#endif
