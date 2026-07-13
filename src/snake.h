#ifndef SNAKE_H
#define SNAKE_H

#include <gb/gb.h>
#include <stdbool.h>
#include "constants.h"
#include "sprites.h"
#include "random.h"

extern uint8_t move_dir;

void init_snake(void);
void move_snake(void);
bool point_in_snake_path(uint8_t, uint8_t);

#endif