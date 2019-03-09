#include <stdlib.h>

#include "./define.h"
#include "./player.h"

UINT8 _PLAYER_FRAMES_DOWN[] = {0x00, 0x04};
UINT8 _PLAYER_FRAMES_UP[] = {0x20, 0x24};
UINT8 _PLAYER_FRAMES_RIGHT[] = {0x44, 0x40};

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
    player->screen_x = PLAYER_CENTER_X;
    player->screen_y = PLAYER_CENTER_Y;
    player->dx = 0;
    player->dy = 1;
    player->_walk_to_count = 0;
    player->_is_walking = FALSE;
    player->_anim_current = player->anim_down;

    return player;
}

// -1 <= dx <= 1
// -1 <= dy <= 1
void player_walk_to_cell(Player* player, Map* map, INT8 dx, INT8 dy) {
    Sprite16Anim* target_anim = NULL;

    player->_is_walking = TRUE;

    // Already in movement
    if (player->_walk_to_count) {
        return;
    }

    // Avoid moving both verticaly and horizontaly
    if (dx) {
        dy = 0;
    }

    // Animate
    if (dx) {
        if (dx == 1) {
            target_anim = player->anim_right;
        } else {
            target_anim = player->anim_left;
        }
    } else if (dy) {
        if (dy == 1) {
            target_anim = player->anim_down;
        } else {
            target_anim = player->anim_up;
        }
    }

    // Update direction
    player->dx = dx;
    player->dy = dy;

    if (target_anim != NULL) {
        if (target_anim != player->_anim_current) {
            sprite16anim_stop(player->_anim_current);
        }
        player->_anim_current = target_anim;
        sprite16anim_play(target_anim);
    }

    // Check for collision
    if (!map_cell_is_walkable(
                map,
                map->x + dx * 2 + player->screen_x,
                map->y + dy * 2 + player->screen_y)) {
        return;
    }

    // Move
    player->_walk_to_count = MAP_CELL_SIZE;
}

void player_update(Player* player, Map* map) {
    // Update animation
    if (!player->_is_walking) {
        sprite16anim_stop(player->_anim_current);
    }
    // Move player
    if (player->_walk_to_count) {
        player->_walk_to_count -= 1;
        map_scroll(map, player->dx, player->dy);
    }
    if (!player->_walk_to_count) {
        player->_is_walking = FALSE;
    }
}

void _player_free(Player* player) {
    // TODO
}
