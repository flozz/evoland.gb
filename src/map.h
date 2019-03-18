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
    UINT8* _bg_map_patch;
};

typedef struct Map Map;

Map* map_new(UINT8* bg_map, UINT8 bg_map_width, UINT8 bg_map_height);
inline void map_cell_patch(Map* map, UINT8 x, UINT8 y);
inline UINT8 map_cell_is_activated(Map* map, UINT8 x, UINT8 y);
void map_cell_set_activated(Map* map, UINT8 x, UINT8 y);
void map_bg_load_chunk(
        Map* map,
        UINT8 sx,
        UINT8 sy,
        UINT8 dx,
        UINT8 dy,
        UINT8 w,
        UINT8 h);
void map_goto(Map* map, UINT8 x, UINT8 y);
void map_scroll(Map* map, INT8 dx, INT8 dy);
UINT8 map_cell_is_walkable(Map* map, UINT8 x, UINT8 y);
void map_free(Map* map);

#endif
