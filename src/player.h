#ifndef _PLAYER_H
#define _PLAYER_H

#include "./map.h"
#include "./sprite16.h"
#include "./sprite16-anim.h"

#define SPRITE_PLAYER 0
#define SPRITE_SWORD  2

struct Player {
    Sprite16* sprite;
    Sprite16* sword;

    Sprite16Anim* anim_down;
    Sprite16Anim* anim_up;
    Sprite16Anim* anim_right;
    Sprite16Anim* anim_left;

    Sprite16Anim* anim_hit_down;
    Sprite16Anim* anim_hit_up;
    Sprite16Anim* anim_hit_right;
    Sprite16Anim* anim_hit_left;

    Sprite16Anim* anim_sword_down;
    Sprite16Anim* anim_sword_up;
    Sprite16Anim* anim_sword_right;
    Sprite16Anim* anim_sword_left;

    UINT8 screen_x;     // x position on screen space (in tile)
    UINT8 screen_y;     // y position on screen space (in tile)
    UINT8 screen_x_px;  // x position on screen space (in px)
    UINT8 screen_y_px;  // y position on screen space (in px)
    INT8 dx;            // Direction x
    INT8 dy;            // Direction y
    UINT8 smooth_scrolling;

    UINT8 _walk_to_count;
    UINT8 _hit_animation_frame_count;
    UINT8 _is_walking;
    UINT8 _is_hitting;

    Sprite16Anim* _anim_current;
    Sprite16Anim* _anim_paused;
    Sprite16Anim* _anim_sword_current;
};

typedef struct Player Player;

Player* player_new();
void player_walk_to_cell(Player* player, Map* map, INT8 dx, INT8 dy);
void player_hit(Player* player);
void player_hit_end(Player* player);
void player_update(Player* player, Map* map);
void player_free(Player* player);

#endif
