#include <gb/gb.h>
#include "../sprites/head_sprite.h"

#define TICK_RATE 30
#define TILE_SIZE 8

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    uint8_t snake_x = 84;
    uint8_t snake_y = 88;

    set_sprite_data(0, 1, HeadSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, snake_x, snake_y);

    uint8_t move_timer = TICK_RATE;

    while(1) {
        if (move_timer <= 0) {
            snake_y -= TILE_SIZE;
            move_sprite(0, snake_x, snake_y);
            move_timer = TICK_RATE;
        }
        move_timer--;
        wait_vbl_done();
    }
}