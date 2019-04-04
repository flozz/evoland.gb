#include <gb/gb.h>

void _fx_wait(UINT8 frames) {
    UINT8 t;
    for (t = 0 ; t < frames ; t++) {
        wait_vbl_done();
    }
}

void fx_bg_fade_in() {
    UINT8 palette = 0xE4;
    UINT8 i;
    BGP_REG = 0x00;
    SHOW_BKG;
    for (i = 8 ; i ; i -= 2) {
        BGP_REG = palette << (i - 2);
        _fx_wait(6);
    }
}

void fx_bg_fade_out() {
    UINT8 palette = 0xE4;
    UINT8 i;
    BGP_REG = palette;
    for (i = 0 ; i <= 6 ; i += 2) {
        BGP_REG = palette << i;
        _fx_wait(6);
    }
    HIDE_BKG;
}
