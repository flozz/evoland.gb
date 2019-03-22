#ifndef _PLAYER_H
#define _PLAYER_H

#include "./map.h"
#include "./sprite16.h"
#include "./sprite16-anim.h"

struct Player {
    Sprite16* sprite;

    Sprite16Anim* anim_down;
    Sprite16Anim* anim_up;
    Sprite16Anim* anim_right;
    Sprite16Anim* anim_left;

    Sprite16Anim* anim_hit_down;
    Sprite16Anim* anim_hit_up;
    Sprite16Anim* anim_hit_right;
    Sprite16Anim* anim_hit_left;

    UINT8 screen_x;  // x position on screen space (in tile)
    UINT8 screen_y;  // y position on screen space (in tile)
    UINT8 dx;        // Direction x
    UINT8 dy;        // Direction y

    UINT8 _walk_to_count;
    UINT8 _hit_animation_frame_count;
    UINT8 _is_walking;
    UINT8 _is_hitting;
    Sprite16Anim* _anim_current;
    Sprite16Anim* _anim_paused;
};

typedef struct Player Player;

Player* player_new();
void player_walk_to_cell(Player* player, Map* map, INT8 dx, INT8 dy);
void player_hit(Player* player);
void player_hit_end(Player* player);
void player_update(Player* player, Map* map);
void _player_free(Player* player);

#endif
