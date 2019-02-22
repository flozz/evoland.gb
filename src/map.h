#ifndef _MAP_H
#define _MAP_H

void map_bg_set(UINT8* map, UINT16 width, UINT16 height);
void map_bg_load_chunk(UINT16 sx, UINT16 sy, UINT8 dx, UINT8 dy, UINT8 w, UINT8 h);
void map_goto(UINT16 x, UINT16 y);
void map_scroll(INT8 dx, INT8 dy);

#endif
