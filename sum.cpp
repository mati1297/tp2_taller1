#include <vector>
#include "sum.h"



void Sum::operate(uint16_t & accumulator, const uint16_t & number) const {
    accumulator += number;
}

uint16_t Sum::getNeutralValue() const {
    return 0;
}