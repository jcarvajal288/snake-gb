#include <gb/gb.h>
#include <rand.h>
#include <types.h>

void init_random(void) {
    waitpad(J_START);
    waitpadup();
    uint16_t seed = DIV_REG;
    seed |= (UWORD)DIV_REG << 8;

    initarand(seed);
}

