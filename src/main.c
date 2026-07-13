#include <gb/gb.h>
#include <gbdk/emu_debug.h>
#include "snake.h"
#include "random.h"

#define TICK_RATE 30

void spawn_apple(void) {
    uint8_t apple_x;
    uint8_t apple_y;
    do {
        apple_x = random_tile_x();
        apple_y = random_tile_y();
    } while (point_in_snake_path(apple_x, apple_y));
    set_sprite_tile(0, 0);
    EMU_printf("apple tile: (%d, %d)\n", apple_x, apple_y);
    EMU_printf("apple coords: (%d, %d)\n", apple_x * TILE_SIZE, apple_y * TILE_SIZE);
    move_sprite(0, apple_x * TILE_SIZE, apple_y * TILE_SIZE);
    // move_sprite(0, 80, 80);
}


void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;
    BGP_REG = 0xE4;

    set_sprite_data(0, 1, apple_sprite);

    init_random();
    init_snake();
    spawn_apple();

    uint8_t move_timer = TICK_RATE;

    while(1) {
        if (move_timer <= 0) {
            move_snake();
            move_timer = TICK_RATE;
        } else {
            move_timer--;
        }
        wait_vbl_done();
    }
}
