#include <gb/gb.h>
#include <gbdk/gbdk-lib.h>
#include <gbdk/emu_debug.h>
#include <stdbool.h>
#include "snake.h"
#include "sprites.h"
#include "random.h"

uint8_t move_dir = MOVE_N;

// an array of snake positions.
// occupied positions are x,y coordinates packed bitwise into a uint16: xxxxxxxxyyyyyyyy.
uint16_t snake_path[NUM_TILES];
uint16_t snake_path_length = 3;


uint8_t snake_map[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

inline uint8_t get_x(uint16_t path_value) {
    return path_value >> 8;
}

inline uint8_t get_y(uint16_t path_value) {
    return path_value & 0xFF;
}

inline uint8_t snake_head_x(void) {
    return get_x(snake_path[0]);
}

inline uint8_t snake_head_y(void) {
    return get_y(snake_path[0]);
}

bool point_in_snake_path(uint8_t x, uint8_t y) {
    uint16_t tile;
    uint8_t snake_x;
    uint8_t snake_y;
    for (uint16_t i = 0; i < snake_path_length; i++) {
        tile = snake_path[i];
        snake_x = get_x(tile);
        snake_y = get_y(tile);
        if (x == snake_x && y == snake_y) {
            return true;
        }
    }
    return false;
}

void set_tile(uint16_t path_index) {
    uint16_t path_value = snake_path[path_index];
    uint8_t x = path_value >> 8;
    uint8_t y = path_value & 0xFF;

    uint8_t tile_value;
    if (path_index == 0) {
        switch(move_dir) {
            case MOVE_N:
                tile_value = HEAD_TILE_N;
                break;
            case MOVE_E:
                tile_value = HEAD_TILE_E;
                break;
            case MOVE_W:
                tile_value = HEAD_TILE_W;
                break;
            default:
                tile_value = HEAD_TILE_S;
                break;
        }
    } else if (path_index == snake_path_length - 1) {
        uint16_t i = 2;
        uint16_t next_tile;
        uint8_t next_x;
        uint8_t next_y;
        // if the snake has just grown the last few tiles are stacked on top of each other
        do {
            next_tile = snake_path[snake_path_length - i];
            next_x = get_x(next_tile);
            next_y = get_y(next_tile);
            i++;
        } while (next_x == x && next_y == y);
        EMU_printf("current: (%d, %d)", x, y);
        EMU_printf("next: (%d, %d)", next_x, next_y);
        if (x < next_x) {
            tile_value = TAIL_TILE_E;
        } else if (x > next_x) {
            tile_value = TAIL_TILE_W;
        } else if (y < next_y) {
            tile_value = TAIL_TILE_N;
        } else {
            tile_value = TAIL_TILE_S;
        }
    } else {
        uint16_t next_tile = snake_path[path_index - 1];
        uint8_t next_x = get_x(next_tile);
        uint8_t next_y = get_y(next_tile);
        uint16_t prev_tile = snake_path[path_index + 1];
        uint8_t prev_x = get_x(prev_tile);
        uint8_t prev_y = get_y(prev_tile);
        bool prev_east = prev_x > x && prev_y == y;
        bool prev_west = prev_x < x && prev_y == y;
        bool prev_north = prev_x == x && prev_y < y;
        bool prev_south = prev_x == x && prev_y > y;
        bool next_east = next_x > x && next_y == y;
        bool next_west = next_x < x && next_y == y;
        bool next_north = next_x == x && next_y < y;
        bool next_south = next_x == x && next_y > y;

        if (prev_north && next_south || prev_south && next_north) {
            tile_value = BODY_VERTICAL_TILE;
        } else if (prev_east && next_west || prev_west && next_east) {
            tile_value = BODY_HORIZONTAL_TILE;
        } 
        else if (prev_north && next_west || prev_west && next_north) {
            tile_value = BODY_BENT_TILE_NW;
        } else if (prev_north && next_east || prev_east && next_north) {
            tile_value = BODY_BENT_TILE_NE;
        } else if (prev_south && next_west || prev_west && next_south) {
            tile_value = BODY_BENT_TILE_SW;
        } else {
            tile_value = BODY_BENT_TILE_SE;
        }
    }

    uint16_t map_index = (y - 1) * TILE_MAP_WIDTH + (x - 1); 
    snake_map[map_index] = tile_value;
}

inline void set_snake_path(uint16_t i, uint16_t x, uint16_t y) {
    snake_path[i] = (x << 8) + y;
}

// TODO: optimize this to only delete tiles that are filled
void clear_snake(void) {
    for (uint16_t i = 0; i < NUM_TILES; i++) {
        snake_map[i] = BLANK_TILE;
    }
    // TODO: this does not delete every tile
    // for(uint16_t i = 0; i < snake_path_length; i++) {
    //     set_tile(snake_map[i], BLANK_TILE);
    // }
}

void draw_snake(void) {
    //set_tile(snake_path[0], HEAD_TILE_N);
    for(int16_t i = 0; i < snake_path_length; i++) {
        set_tile(i);
    }
    //set_tile(snake_path[snake_path_length - 1], TAIL_TILE_S);
    set_bkg_tiles(0, 0, TILE_MAP_WIDTH, TILE_MAP_HEIGHT, snake_map);
}

void init_snake(void) {
    clear_snake();
    set_snake_path(0, 10, 9);
    set_snake_path(1, 10, 10);
    set_snake_path(2, 10, 11);
    snake_path_length = 3;
    move_dir = MOVE_N;

    set_bkg_data(0, NUM_SNAKE_TILES, snake_tiles);
    draw_snake();
}

bool has_hit_wall(void) {
    uint8_t x = get_x(snake_path[0]);
    uint8_t y = get_y(snake_path[0]);
    if (move_dir == MOVE_N && y == 1) {
        return true;
    } else if (move_dir == MOVE_W && x == 1) {
        return true;
    } else if (move_dir == MOVE_E && x == TILE_MAP_WIDTH) {
        return true;
    } else if (move_dir == MOVE_S && y == TILE_MAP_HEIGHT) {
        return true;
    } else {
        return false;
    }
}

void move_snake(void) {
    clear_snake();

    for(uint16_t i = snake_path_length - 1; i > 0; i--) {
        snake_path[i] = snake_path[i - 1];
    }
    if (move_dir == MOVE_N) {
        snake_path[0] = snake_path[0] - 1; // move head up 1 tile
    } else if (move_dir == MOVE_W) {
        snake_path[0] = snake_path[0] - 0x100; // move head left 1 tile
    } else if (move_dir == MOVE_E) {
        snake_path[0] = snake_path[0] + 0x100; // move head right 1 tile
    } else if (move_dir == MOVE_S) {
        snake_path[0] = snake_path[0] + 1; // move head down 1 tile
    }
    uint8_t x = get_x(snake_path[0]);
    uint8_t y = get_y(snake_path[0]);
    draw_snake();
}

void grow_snake(void) {
    snake_path[snake_path_length] = snake_path[snake_path_length - 1];
    snake_path[snake_path_length + 1] = snake_path[snake_path_length - 1];
    snake_path_length += 2;
}

bool snake_eat_itself(void) {
    uint16_t head_tile = snake_path[0];
    uint16_t head_x = get_x(head_tile);
    uint16_t head_y = get_y(head_tile);
    uint16_t current_tile;
    uint8_t current_x;
    uint8_t current_y;
    for (uint16_t i = 1; i < snake_path_length; i++) {
        current_tile = snake_path[i];
        current_x = get_x(current_tile);
        current_y = get_y(current_tile);
        if (head_x == current_x && head_y == current_y) {
            return true;
        }
    }
    return false;
}