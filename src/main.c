#include <gb/gb.h>

#include "./define.h"
#include "./sprite16-anim.h"
#include "./game.h"
#include "./menu.h"

void main(void) {
    sprite16anim_init();
    // TODO Logo screen

    while (TRUE) {
        menu_main();

        game_init();
        game_main();
        game_end();

        // TODO Game Over screen
    }
}

