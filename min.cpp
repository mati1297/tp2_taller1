#include <algorithm>
#include <vector>
#include "min.h"


void Min::accumulate(uint16_t & accumulator, const uint16_t & number) const {
    accumulator = std::min(accumulator, number);
}

uint16_t Min::getNeutralValue() const {
    return UINT16_MAX;
}



