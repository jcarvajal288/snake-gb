#include <gb/gb.h>
#include <gbdk/emu_debug.h>
#include "snake.h"
#include "random.h"

#define TICK_RATE 30

uint8_t apple_x;
uint8_t apple_y;

void spawn_apple(void) {
    do {
        apple_x = random_tile_x();
        apple_y = random_tile_y();
    } while (point_in_snake_path(apple_x, apple_y));
    EMU_printf("Apple spawn: (%d, %d)\n", apple_x, apple_y);
    move_sprite(0, apple_x * TILE_SIZE, apple_y * TILE_SIZE + 8);
}

void eat_apple(void) {
    spawn_apple();
    // grow_snake();
}

void read_joypad(void) {
    if (joypad() & J_UP && move_dir != MOVE_S) {
        move_dir = MOVE_N;
    } else if (joypad() & J_LEFT && move_dir != MOVE_E) {
        move_dir = MOVE_W;
    } else if (joypad() & J_RIGHT && move_dir != MOVE_W) {
        move_dir = MOVE_E;
    } else if (joypad() & J_DOWN && move_dir != MOVE_N) {
        move_dir = MOVE_S;
    } 
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
    set_sprite_tile(0, 0);

    uint8_t move_timer = TICK_RATE;

    while(1) {
        read_joypad();
        if (move_timer <= 0) {
            move_snake();
            EMU_printf("Snake head: (%d, %d)\n", snake_head_x(), snake_head_y());
            if (snake_head_x() == apple_x && snake_head_y() == apple_y) {
                eat_apple();
            }
            move_timer = TICK_RATE;
        } else {
            move_timer--;
        }
        wait_vbl_done();
    }
}
