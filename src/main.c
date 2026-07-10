#include <gb/gb.h>
#include "../sprites/head_sprite.h"

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    set_sprite_data(0, 1, HeadSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 84, 88);

    while(1) {
        wait_vbl_done();
    }
}