#ifndef RANDOM_H
#define RANDOM_H

#include <gb/gb.h>
#include <rand.h>

#define SCREEN_TILE_WIDTH (SCREENWIDTH / 8)
#define SCREEN_TILE_HEIGHT (SCREENHEIGHT / 8)

#define RAND_RANGE_8BIT(randval, range) (uint8_t)(((randval & 0xFFu) * range) >> 8)

void init_random(void);

static inline uint8_t random_range(uint8_t lower, uint8_t upper) {
    return RAND_RANGE_8BIT(rand(), upper - lower) + lower;
}

static inline uint8_t random_tile_x(void) {
    return random_range(0, SCREEN_TILE_WIDTH) * 8;
}

static inline uint8_t random_tile_y(void) {
    return random_range(0, SCREEN_TILE_HEIGHT) * 8;
}

#endif