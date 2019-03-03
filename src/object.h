#ifndef _OBJECT_H
#define _OBJECT_H

#include <types.h>

#include "./sprite16.h"

struct Object {
    UINT8 tile_id;
    UINT16 x;           // Map x
    UINT16 y;           // Map y
    UINT8 state;        // Reserved field
    UINT8 action_mask;  // Key mask that activate this object
    void* callback;     // Callback function called when the object is activated
    Sprite16* _sprite;  // The used sprite when active
};

typedef struct Object Object;

Object* object_new(
        UINT8 tile_id,
        UINT16 x,
        UINT16 y,
        UINT8 action_mask,
        void* callback);
UINT8 object_is_active(Object* object);
void object_enable(Object* object);
void object_disable(Object* object);
void object_update_all(UINT16 map_x, UINT16 map_y, UINT8 dx, UINT8 dy);
void object_free(Object* object);

#endif
