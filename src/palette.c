#include <types.h>
#include <gb/hardware.h>

#include "./palette.h"

#define _PALETTE_CALC color0 | color1 << 2 | color2 << 4 | color3 << 6;

void palette_set_bgp(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3) {
    BGP_REG = _PALETTE_CALC;
}

void palette_set_obp0(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3) {
    OBP0_REG = _PALETTE_CALC;
}

void palette_set_obp1(UINT8 color0, UINT8 color1, UINT8 color2, UINT8 color3) {
    OBP1_REG = _PALETTE_CALC;
}
