#include <gb/gb.h>
#include "../sprites/head_sprite.h"

#define TILE_SIZE 8

uint8_t snake_x = 84;
uint8_t snake_y = 88;

void init_snake(void) {
    set_sprite_data(0, 1, HeadSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, snake_x, snake_y);
}

void move_snake(void) {
    snake_y -= TILE_SIZE;
    move_sprite(0, snake_x, snake_y);
}