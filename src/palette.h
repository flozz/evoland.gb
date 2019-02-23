#ifndef _PALETTE_H
#define _PALETTE_H

#include <types.h>

#define PALETTE_WHITE  0
#define PALETTE_SILVER 1
#define PALETTE_GRAY   2
#define PALETTE_BLACK  3

void palette_set_bgp(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3);
void palette_set_obp0(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3);
void palette_set_obp1(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3);

#endif
