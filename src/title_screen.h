/**
 * title_screen.h
 *
 * Generated with game-boy-tile-tools.calvin.sh
 */

#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include <stdint.h>

#define TITLE_SCREEN_TILE_WIDTH 8
#define TITLE_SCREEN_TILE_HEIGHT 8
#define TITLE_SCREEN_WIDTH 20
#define TITLE_SCREEN_HEIGHT 18
#define TITLE_SCREEN_TILE_COUNT 23
#define TITLE_SCREEN_MAP_SIZE 360
#define TITLE_SCREEN_TILE_OFFSET 0

extern const unsigned char title_screen_tiles[TITLE_SCREEN_TILE_COUNT * 16];
extern const unsigned char title_screen_map[TITLE_SCREEN_MAP_SIZE];

#endif