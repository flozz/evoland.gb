#ifndef _MAP_H
#define _MAP_H

#include <types.h>

#define MAP_CELL_SIZE 16
#define MAP_WALKABLE_THRESHOLD 0x60

struct Map {
    UINT8 x;
    UINT8 y;
    UINT8* bg_map;
    UINT8 bg_map_width;
    UINT8 bg_map_height;
    UINT8 _bg_layer_x;
    UINT8 _bg_layer_y;
};

typedef struct Map Map;

Map* map_new(UINT8* bg_map, UINT8 bg_map_width, UINT8 bg_map_height);
//void map_bg_set(UINT8* map, UINT16 width, UINT16 height);
void map_bg_load_chunk(
        Map* map,
        UINT8 sx,
        UINT8 sy,
        UINT8 dx,
        UINT8 dy,
        UINT8 w,
        UINT8 h);
//void map_get_coord(UINT16* x, UINT16* y);
void map_goto(Map* map, UINT8 x, UINT8 y);
void map_scroll(Map* map, INT8 dx, INT8 dy);
UINT8 map_cell_is_walkable(Map* map, UINT8 x, UINT8 y);
void map_free(Map* map);

#endif
