#include <gb/gb.h>

#include "./fx.h"
#include "./gassets/evoland_logo.tileset.h"
#include "./gassets/evoland_logo.tilemap.h"

void menu_main() {
    set_bkg_data(0, EVOLAND_LOGO_TILESET_TILE_COUNT, EVOLAND_LOGO_TILESET);
    set_bkg_tiles(
            1, 1,
            EVOLAND_LOGO_TILEMAP_WIDTH,
            EVOLAND_LOGO_TILEMAP_HEIGHT,
            EVOLAND_LOGO_TILEMAP);
    fx_bg_fade_in();
    waitpad(J_START | J_A | J_B);
    fx_bg_fade_out();
}
