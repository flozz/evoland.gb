#include <stdlib.h>

#include <gb/gb.h>

#include "text.h"

// String must be zero-terminated (\0)
UINT8* text_map_string(char* string, UINT8 width, UINT8 height) {
    UINT8* text_map = malloc(sizeof(UINT8) * width * height);
    UINT8 c;
    UINT8 i = 0;
    UINT8 x = 0;
    UINT8 y = 0;

    if (text_map == NULL) {
        return NULL;
    }

    for (i = 0 ; i < width * height ; i += 1) {
        text_map[i] = TEXT_TILE_BLANK;
    }

    i = 0;

    while (c = string[i]) {
        i += 1;
        if (c == TEXT_CHAR_NEWLINE) {
            x = 0;
            y += 1;
            continue;
        }
        if (y >= height) {
            break;
        }
        if (x >= width) {
            continue;
        }
        if (c >= TEXT_CHAR_START && c <= TEXT_CHAR_END) {
            text_map[y * width + x] = TEXT_TILE_OFFSET + c - TEXT_CHAR_START;
        } else if (c >= TEXT_CHAR_LOWER_START && c <= TEXT_CHAR_LOWER_END) {
            text_map[y * width + x] = TEXT_TILE_LOWER_OFFSET + c - TEXT_CHAR_LOWER_START;
        } else {
            text_map[y * width + x] = TEXT_TILE_DEFAULT;
        }
        x += 1;
    }

    return text_map;
}

void text_free_map(UINT8* text) {
    free(text);
}

// String must be zero-terminated (\0)
void text_show_message(char* string) {
    // TODO
}
