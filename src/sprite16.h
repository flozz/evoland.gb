#ifndef _SPRITE16_H
#define _SPRITE16_H

#include <gb/gb.h>

// WARNING: when using Sprite16, the 16x16 sprite will use 2 GameBoy 8x16 sprites.
// The used sprites will be "sprite_id" and "sprite_id + 1"

struct Sprite16 {
    UINT8 id;
    UINT8 x;
    UINT8 y;
};

typedef struct Sprite16 Sprite16;

Sprite16* sprite16_new(UINT8 sprite_id, UINT8 tile_id, UINT8 x, UINT8 y);
void sprite16_set_tile(Sprite16* sprite, UINT8 tile_id);
void sprite16_set_position(Sprite16* sprite, UINT8 x, UINT8 y);
void sprite16_destroy(Sprite16* sprite);

#endif
