#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

uint16_t get_bit(uint16_t, uint16_t);

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t n0 = get_bit(*reg, 0);
    uint16_t n2 = get_bit(*reg, 2);
    uint16_t n3 = get_bit(*reg, 3);
    uint16_t n5 = get_bit(*reg, 5);
    uint16_t restore = n0 ^ n2 ^ n3 ^ n5;
    uint16_t tmp = restore << 15;
    (*reg) = ((*reg) >> 1) | tmp;
}

uint16_t get_bit(uint16_t num, uint16_t n) {
    return (num >> n) & 1;
}