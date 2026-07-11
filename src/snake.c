#include <gb/gb.h>
#include <stdbool.h>
#include "sprites.h"
#include "random.h"

#define TILE_SIZE 8

uint8_t snake_x = 84;
uint8_t snake_y = 88;


void init_snake(void) {
    set_sprite_data(0, 1, HeadSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, snake_x, snake_y);
}

inline bool has_collided(void) {
    return snake_y <= 0;
}

void move_snake(void) {
    snake_y -= TILE_SIZE;
    if (has_collided()) {
        snake_x = random_tile_x();
        snake_y = random_tile_y();
    }
    move_sprite(0, snake_x, snake_y);
}
