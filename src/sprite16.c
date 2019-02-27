#include <stdlib.h>
#include <gb/gb.h>

#include "./define.h"
#include "./sprite16.h"

Sprite16* sprite16_new(UINT8 sprite_id, UINT8 tile_id, UINT8 x, UINT8 y) {
    Sprite16* sprite = malloc(sizeof(Sprite16));

    if (sprite == NULL) {
        return NULL;
    }

    sprite->id = sprite_id;
    sprite->flipx = FALSE;
    sprite16_set_tile(sprite, tile_id);
    sprite16_set_position(sprite, x, y);

    return sprite;
}

void sprite16_set_tile(Sprite16* sprite, UINT8 tile_id) {
    if (!sprite->flipx) {
        set_sprite_tile(sprite->id, tile_id);
        set_sprite_tile(sprite->id + 1, tile_id + 2);
    } else {
        set_sprite_tile(sprite->id, tile_id + 2);
        set_sprite_tile(sprite->id + 1, tile_id);
    }
}

void sprite16_set_position(Sprite16* sprite, UINT8 x, UINT8 y) {
    sprite->x = x;
    sprite->y = y;
    move_sprite(sprite->id, x, y);
    move_sprite(sprite->id + 1, x + GB_TILE_SIZE, y);
}

void sprite16_set_flipx(Sprite16* sprite, UINT8 flipx) {
    UINT8 tile_id;
    if (flipx == sprite->flipx) {
        return;
    }
    sprite->flipx = flipx;
    // Swap sprites' tiles
    tile_id = get_sprite_tile(sprite->id);
    set_sprite_tile(sprite->id, get_sprite_tile(sprite->id + 1));
    set_sprite_tile(sprite->id + 1, tile_id);
    // Enamble / remove mirror on sprites
    if (flipx) {
        set_sprite_prop(sprite->id, get_sprite_prop(sprite->id) | S_FLIPX);
        set_sprite_prop(sprite->id + 1, get_sprite_prop(sprite->id + 1) | S_FLIPX);
    } else {
        set_sprite_prop(sprite->id, get_sprite_prop(sprite->id) & ~S_FLIPX);
        set_sprite_prop(sprite->id + 1, get_sprite_prop(sprite->id + 1) & ~S_FLIPX);
    }

}

void sprite16_free(Sprite16* sprite) {
    if (sprite == NULL) {
        return;
    }

    free(sprite);
}
