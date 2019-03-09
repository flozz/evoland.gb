#ifndef _PLAYER_H
#define _PLAYER_H

#include "./map.h"
#include "./sprite16.h"
#include "./sprite16-anim.h"

#define PLAYER_CENTER_X 9
#define PLAYER_CENTER_Y 8

struct Player {
    Sprite16* sprite;
    Sprite16Anim* anim_down;
    Sprite16Anim* anim_up;
    Sprite16Anim* anim_right;
    Sprite16Anim* anim_left;
    UINT8 screen_x;  // x position on screen space (in tile)
    UINT8 screen_y;  // y position on screen space (in tile)
    UINT8 dx;        // Direction x
    UINT8 dy;        // Direction y
    UINT8 _walk_to_count;
    UINT8 _is_walking;
    Sprite16Anim* _anim_current;
};

typedef struct Player Player;

Player* player_new();
void player_walk_to_cell(Player* player, Map* map, INT8 dx, INT8 dy);
void player_update(Player* player, Map* map);
void _player_free(Player* player);

#endif
