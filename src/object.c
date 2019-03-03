#include <stdlib.h>

#include "./define.h"
#include "./object.h"

#define OBJECT_SPRITE_POOL_START 20
#define OBJECT_SPRITE_POOL_SIZE  10

Object* _object_pool[OBJECT_SPRITE_POOL_SIZE];


void object_init() {
    UINT8 i;
    for (i = 0 ; i < OBJECT_SPRITE_POOL_SIZE ; i++) {
        _object_pool[i] = NULL;
    }
}

Object* object_new(
        UINT8 tile_id,
        UINT16 x,
        UINT16 y,
        UINT8 action_mask,
        void* callback) {
    Object* object = malloc(sizeof(Object));

    if (object == NULL) {
        return NULL;
    }

    object->tile_id = tile_id;
    object->x = x;
    object->y = y;
    object->state = 0;
    object->action_mask = action_mask;
    object->callback = callback;
    object->_sprite = NULL;

    return object;
}

UINT8 object_is_active(Object* object) {
    if (object->_sprite == NULL) {
        return FALSE;
    }
    return TRUE;
}

void object_enable(Object* object) {
    UINT8 i;

    if (object_is_active(object)) {
        return;
    }

    for (i = 0 ; i < OBJECT_SPRITE_POOL_SIZE ; i++) {
        if (_object_pool[i] != NULL) {
            continue;
        }
        _object_pool[i] = object;
        object->_sprite = sprite16_new(
                OBJECT_SPRITE_POOL_START + i * 2,
                object->tile_id,
                0, 0);
        break;
    }
}

void object_disable(Object* object) {
    UINT8 i;
    for (i = 0 ; i < OBJECT_SPRITE_POOL_SIZE ; i++) {
        if (_object_pool[i] != object) {
            continue;
        }
        _object_pool[i] = NULL;
        sprite16_hide(object->_sprite);
        sprite16_free(object->_sprite);
        object->_sprite = NULL;
        break;
    }
}

void object_update_all(UINT16 map_x, UINT16 map_y, UINT8 dx, UINT8 dy) {
    UINT8 i;
    Object* object;

    for (i = 0 ; i < OBJECT_SPRITE_POOL_SIZE ; i++) {
        if (_object_pool[i] == NULL) {
            continue;
        }
        object = _object_pool[i];
        sprite16_set_position(
                object->_sprite,
                (object->x - map_x) * GB_TILE_SIZE - dx + 8, // FIXME
                (object->y - map_y) * GB_TILE_SIZE - dy);
    }
}

void object_free(Object* object) {
    // TODO
}
