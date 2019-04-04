#ifndef _TEXT_H
#define _TEXT_H

#include <types.h>

#define TEXT_TILE_DEFAULT      0x0E
#define TEXT_TILE_BLANK        0xC0
#define TEXT_CHAR_NEWLINE      0x0A

#define TEXT_TILE_OFFSET       0xC0
#define TEXT_CHAR_START        0x20
#define TEXT_CHAR_END          0x5F

#define TEXT_TILE_LOWER_OFFSET 0xE1
#define TEXT_CHAR_LOWER_START  0x61
#define TEXT_CHAR_LOWER_END    0x7A

#define TEXT_TILE_BORDER       0xFE

void text_load_font();
inline void text_map_char(char c, UINT8* buff);
UINT8* text_map_string(char* string, UINT8 width, UINT8 height);
void text_free_map(UINT8* text);
void text_show_message(char* string, UINT8 pannel_height);

#endif
