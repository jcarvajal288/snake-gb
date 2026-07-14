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

void play_move_sound(void) {
    NR10_REG = 0x70;
    NR11_REG = 0x57;
    NR12_REG = 0x42;
    NR13_REG = 0x17;
    NR14_REG = 0x84;
}

void play_loss_sound(void) {
    NR10_REG = 0x4A;
    NR11_REG = 0x43;
    NR12_REG = 0x42;
    NR13_REG = 0x30;
    NR14_REG = 0x80;

    delay(100);

    NR10_REG = 0x4A;
    NR11_REG = 0x43;
    NR12_REG = 0x42;
    NR13_REG = 0x30;
    NR14_REG = 0x80;
}