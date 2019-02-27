#ifndef _SPRITE16_ANIM_H
#define _SPRITE16_ANIM_H

#include <types.h>

#include "./sprite16.h"

struct Sprite16Anim {
    Sprite16* sprite;      // The Sprite16 to animate
    UINT8 frame_skip;      // Speed of the animation (number of frame to skip)
    UINT8 frame_count;     // Number of frame in the animation
    UINT8* frames;         // List of the frame of the animation
    UINT8 flipx;           // Mirror the sprite?
    UINT8 _next_frame_id;  // (priv) Next frame to display
    UINT8 _frame_counter;  // (priv) remaining frame to skip
};

typedef struct Sprite16Anim Sprite16Anim;

void sprite16anim_init();
UINT8 sprite16anim_is_playing(Sprite16Anim* anim);
Sprite16Anim* sprite16anim_new(
        Sprite16* sprite,
        UINT8 fps,
        UINT8 frame_count,
        UINT8* frames,
        UINT8 xflip);
void sprite16anim_play(Sprite16Anim* anim);
void sprite16anim_stop(Sprite16Anim* anim);
void sprite16anim_loop();
void sprite16anim_free(Sprite16Anim* anim);

#endif
