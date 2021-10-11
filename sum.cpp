#include "sum.h"

void Sum::accumulate(uint16_t & accumulator, const uint16_t & number) const {
    accumulator += number;
}

uint16_t Sum::getNeutralValue() const {
    return 0;
}
