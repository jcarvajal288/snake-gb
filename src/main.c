#include <gb/gb.h>
#include "snake.h"
#include "random.h"

#define TICK_RATE 30

void main(void) {
    DISPLAY_ON;
    SHOW_SPRITES;

    init_random();
    init_snake();

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
