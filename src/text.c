#include <stdlib.h>

#include <gb/gb.h>

#include "./define.h";
#include "text.h"

inline void text_map_char(char c, UINT8* buff) {
    if (c >= TEXT_CHAR_START && c <= TEXT_CHAR_END) {
        *buff = TEXT_TILE_OFFSET + c - TEXT_CHAR_START;
    } else if (c >= TEXT_CHAR_LOWER_START && c <= TEXT_CHAR_LOWER_END) {
        *buff = TEXT_TILE_LOWER_OFFSET + c - TEXT_CHAR_LOWER_START;
    } else {
        *buff = TEXT_TILE_DEFAULT;
    }
}

// String must be zero-terminated (\0)
UINT8* text_map_string(char* string, UINT8 width, UINT8 height) {
    UINT8* text_map = malloc(sizeof(UINT8) * width * height);
    char c;
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
        text_map_char(c, text_map + (y * width + x));
        x += 1;
    }

    return text_map;
}

void text_free_map(UINT8* text) {
    free(text);
}

void _text_clear_message(UINT8 height, UINT8 offset, UINT8 tile_id) {
    UINT8 i;
    UINT8 line[GB_SCREEN_WIDTH];
    for (i = 0 ; i < GB_SCREEN_WIDTH ; i++) {
        line[i] = tile_id;
    }
    for (i = offset ; i < height ; i++) {
        set_win_tiles(0, i, GB_SCREEN_WIDTH, 1, line);
    }
}

// String must be zero-terminated (\0)
void text_show_message(char* string, UINT8 pannel_height) {
    char c;
    UINT8 text;
    UINT8 x = 0;
    UINT8 y = 1;
    UINT16 i = 0;

    _text_clear_message(1, 0, TEXT_TILE_BORDER);
    _text_clear_message(pannel_height, 1, TEXT_TILE_BLANK);

    // Show pannel
    move_win(7, GB_SCREEN_HEIGHT * GB_TILE_SIZE);
    SHOW_WIN;
    for (i = GB_SCREEN_HEIGHT * GB_TILE_SIZE ; i >= (GB_SCREEN_HEIGHT - pannel_height) * GB_TILE_SIZE ; i -= 4) {
        move_win(7, i);
        wait_vbl_done();
    }

    // Display text
    i = 0;
    while (c = string[i++]) {
        if (c == TEXT_CHAR_NEWLINE) {
            x = 0;
            y += 1;
            if (y >= pannel_height) {
                waitpad(J_A | J_B);
                waitpadup();
                _text_clear_message(pannel_height, 1, TEXT_TILE_BLANK);
                x = 0;
                y = 1;
            }
            continue;
        }
        if (x >= GB_SCREEN_WIDTH) {
            continue;
        }
        text_map_char(c, &text);
        set_win_tiles(x, y, 1, 1, &text);
        x += 1;
        wait_vbl_done();
    }

    waitpad(J_A | J_B);
    waitpadup();

    // Hide pannel
    for (i = (GB_SCREEN_HEIGHT - pannel_height) * GB_TILE_SIZE ; i <= GB_SCREEN_HEIGHT * GB_TILE_SIZE ; i += 4) {
        move_win(7, i);
        wait_vbl_done();
    }
    HIDE_WIN;
}
