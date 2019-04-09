#include <gb/gb.h>

#include "./text.h"
#include "./objects/chests.objects.h"


UINT8 chest_get_id(UINT8 x, UINT8 y) {
    UINT8 i;
    for (i = 0 ; i < CHESTS_COUNT ; i += 1) {
        if (CHESTS[i * 3] != x) {
            continue;
        }
        if (CHESTS[i * 3 + 1] != y) {
            continue;
        }
        return CHESTS[i * 3 + 2];
    }
    return 255;
}

void chest_activate(UINT8 chest_id) {
    switch(chest_id) {
        case 0:
            text_show_message("CHEST 0\0", 4);  // FIXME
            break;
        case 1:
            text_show_message("CHEST 1\0", 4);  // FIXME
            break;
        default:
            text_show_message("...\0", 4);  // FIXME
    }
}
