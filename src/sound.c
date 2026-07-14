#include <gb/gb.h>
#include "sound.h"

void init_sound(void) {
    NR52_REG = 0x80; // turns on sound
    NR50_REG = 0x77; // sets both left and right channel volume to max
    NR51_REG = 0xFF; // use all channels
}

void play_eat_apple_sound(void) {
    NR10_REG = 0x15;
    NR11_REG = 0x8D;
    NR12_REG = 0x73;
    NR13_REG = 0xA4;
    NR14_REG = 0x83;
}
