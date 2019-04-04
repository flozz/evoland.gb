#include <gb/gb.h>

#include "./fx.h"
#include "./text.h"
#include "./gassets/evoland_logo.tileset.h"
#include "./gassets/evoland_logo.tilemap.h"

void menu_main() {
    UINT8* text;

    set_bkg_data(0, EVOLAND_LOGO_TILESET_TILE_COUNT, EVOLAND_LOGO_TILESET);
    text_load_font();

    set_bkg_tiles(
            1, 1,
            EVOLAND_LOGO_TILEMAP_WIDTH,
            EVOLAND_LOGO_TILEMAP_HEIGHT,
            EVOLAND_LOGO_TILEMAP);

    text = text_map_string("PRESS START!\n", 13, 1);
    set_bkg_tiles(4, 14, 13, 1, text);
    text_free_map(text);

    fx_bg_fade_in();
    waitpad(J_START | J_A | J_B);
    fx_bg_fade_out();
}
