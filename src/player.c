#include <stdlib.h>

#include "./define.h"
#include "./player.h"
#include "./map.h"

UINT8 _PLAYER_FRAMES_DOWN[] = {0x00, 0x04};
UINT8 _PLAYER_FRAMES_UP[] = {0x20, 0x24};
UINT8 _PLAYER_FRAMES_RIGHT[] = {0x44, 0x40};

Player* _player;

void player_init() {
    _player = player_new();
}

Player* player_new() {
    Player* player = malloc(sizeof(Player));

    if (player == NULL) {
        return NULL;
    }

    player->sprite = sprite16_new(0, _PLAYER_FRAMES_DOWN[0], 80, 80);
    player->anim_down = sprite16anim_new(player->sprite, 6, 2, _PLAYER_FRAMES_DOWN, FALSE);
    player->anim_up = sprite16anim_new(player->sprite, 6, 2, _PLAYER_FRAMES_UP, FALSE);
    player->anim_right = sprite16anim_new(player->sprite, 6, 2, _PLAYER_FRAMES_RIGHT, FALSE);
    player->anim_left = sprite16anim_new(player->sprite, 6, 2, _PLAYER_FRAMES_RIGHT, TRUE);
    player->_walk_to_count = 0;
    player->_is_walking = FALSE;

    return player;
}

// -1 <= dx <= 1
// -1 <= dy <= 1
void player_walk_to_cell(INT8 dx, INT8 dy) {
    UINT16 map_x;
    UINT16 map_y;

    _player->_is_walking = TRUE;

    // Already in movement
    if (_player->_walk_to_count) {
        return;
    }

    // Animate
    if (dx) {
        if (dx == 1) {
            sprite16anim_play(_player->anim_right);
        } else {
            sprite16anim_play(_player->anim_left);
        }
    } else if (dy) {
        if (dy == 1) {
            sprite16anim_play(_player->anim_down);
        } else {
            sprite16anim_play(_player->anim_up);
        }
    }


    // Avoid moving both verticaly and horizontaly
    if (dx) {
        dy = 0;
    }

    // Check for collision
    map_get_coord(&map_x, &map_y);
    if (!map_cell_is_walkable(map_x + dx*2, map_y + dy*2)) {
        return;
    }

    // Move
    _player->_walk_to_dx = dx;
    _player->_walk_to_dy = dy;
    _player->_walk_to_count = MAP_CELL_SIZE;
}

void player_loop() {
    // Update animation
    if (!_player->_is_walking) {
        sprite16anim_stop(_player->anim_down);
        sprite16anim_stop(_player->anim_up);
        sprite16anim_stop(_player->anim_right);
        sprite16anim_stop(_player->anim_left);
    }
    // Move player
    if (_player->_walk_to_count) {
        _player->_walk_to_count -= 1;
        map_scroll(_player->_walk_to_dx, _player->_walk_to_dy);
    }
    if (!_player->_walk_to_count) {
        _player->_is_walking = FALSE;
    }
}

void _player_free(Player* player) {
    // TODO
}
