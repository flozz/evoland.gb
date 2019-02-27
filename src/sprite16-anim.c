#include <stdlib.h>

#include "./define.h"
#include "./sprite16-anim.h"

#define SPRITE16ANIM_MAX 10

Sprite16Anim* _sprite16anim_playing[10];

void sprite16anim_init() {
    UINT8 i;
    for (i = 0 ; i < SPRITE16ANIM_MAX ; i++) {
        _sprite16anim_playing[i] = NULL;
    }
}

Sprite16Anim* sprite16anim_new(
        Sprite16* sprite,
        UINT8 fps,
        UINT8 frame_count,
        UINT8* frames,
        UINT8 xflip) {
    Sprite16Anim* anim = malloc(sizeof(Sprite16Anim));

    if (anim == NULL) {
        return NULL;
    }

    anim->sprite = sprite;
    anim->frame_skip = GB_FPS / fps;
    anim->frame_count = frame_count;
    anim->frames = frames;
    anim->xflip = xflip;
    return anim;
}

void sprite16anim_play(Sprite16Anim* anim) {
    UINT8 i;
    anim->_next_frame_id = 0;
    anim->_frame_counter = anim->frame_skip;
    for (i = 0 ; i < SPRITE16ANIM_MAX ; i++) {
        if (_sprite16anim_playing[i] == NULL) {
            _sprite16anim_playing[i] = anim;
            break;
        }
    }
}

void sprite16anim_stop(Sprite16Anim* anim) {
    UINT8 i;
    for (i = 0 ; i < SPRITE16ANIM_MAX ; i++) {
        if (_sprite16anim_playing[i] == anim) {
            _sprite16anim_playing[i] = NULL;
            break;
        }
    }
}

void sprite16anim_loop() {
    UINT8 i;
    Sprite16Anim* anim = NULL;
    for (i = 0 ; i < SPRITE16ANIM_MAX ; i++) {
        anim = _sprite16anim_playing[i];
        if (anim == NULL) {
            continue;
        }
        if (!anim->_frame_counter) {
            sprite16_set_tile(anim->sprite, anim->frames[anim->_next_frame_id]);
            anim->_next_frame_id = (anim->_next_frame_id + 1) % anim->frame_count;
            anim->_frame_counter = anim->frame_skip;
        } else {
            anim->_frame_counter -= 1;
        }
    }
}

void sprite16anim_free(Sprite16Anim* anim) {
    if (anim == NULL) {
        return;
    }

    free(anim);
}
