#ifndef METASPRITE_sprites_H
#define METASPRITE_sprites_H

#include <stdint.h>

#define NUM_SNAKE_TILES 15

#define BLANK_TILE 0x00
#define HEAD_TILE_N 0x01
#define HEAD_TILE_W 0x02
#define HEAD_TILE_E 0x03
#define HEAD_TILE_S 0x04
#define BODY_VERTICAL_TILE 0x05
#define BODY_HORIZONTAL_TILE 0x06
#define BODY_BENT_TILE_NE 0x07
#define BODY_BENT_TILE_SE 0x08
#define BODY_BENT_TILE_SW 0x09
#define BODY_BENT_TILE_NW 0x0a
#define TAIL_TILE_N 0x0b
#define TAIL_TILE_W 0x0c
#define TAIL_TILE_E 0x0d
#define TAIL_TILE_S 0x0e

extern const uint8_t snake_tiles[0x10 * NUM_SNAKE_TILES];

extern const uint8_t apple_sprite[16];

#endif