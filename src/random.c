#include <gb/gb.h>
#include <rand.h>
#include <types.h>

void init_random(void) {
    uint16_t seed = DIV_REG;
    seed |= (UWORD)DIV_REG << 8;

    initarand(seed);
}

