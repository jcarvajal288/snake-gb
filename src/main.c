#include <gb/gb.h>
#include <gbdk/emu_debug.h>
#include "constants.h"
#include "random.h"
#include "snake.h"
#include "sound.h"
#include "title_screen.h"

uint8_t apple_x;
uint8_t apple_y;

void spawn_apple(void) {
    do {
        // need to add 1 to account for move_sprite subtracting -8,-16 to all sprite positions
        apple_x = random_tile_x() + 1;
        apple_y = random_tile_y() + 1;
    } while (point_in_snake_path(apple_x, apple_y));
    move_sprite(0, apple_x * TILE_SIZE, apple_y * TILE_SIZE + 8); 
}

void eat_apple(void) {
    spawn_apple();
    play_eat_apple_sound();
    grow_snake();
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

    init_sound();

    set_sprite_data(0, 1, apple_sprite);
    set_sprite_tile(0, 0);

    set_bkg_data(TITLE_SCREEN_TILE_OFFSET, TITLE_SCREEN_TILE_COUNT, title_screen_tiles);
    set_bkg_tiles(0, 0, TITLE_SCREEN_WIDTH, TITLE_SCREEN_HEIGHT, title_screen_map);
    init_random();
    init_snake();
    spawn_apple();

    uint8_t move_timer = TICK_RATE;

    while(1) {
        read_joypad();
        if (move_timer <= 0) {
            move_snake();
            if (snake_head_x() == apple_x && snake_head_y() == apple_y) {
                eat_apple();
            } else if (snake_eat_itself()) {
                init_snake();
                spawn_apple();
            }
            move_timer = TICK_RATE;
        } else {
            move_timer--;
        }
        wait_vbl_done();
    }
}
