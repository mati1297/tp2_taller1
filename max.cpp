#include <vector>
#include <algorithm>
#include "max.h"


void Max::accumulate(uint16_t & accumulator, const uint16_t & number) const {
    accumulator = std::max(accumulator, number);
}

uint16_t Max::getNeutralValue() const {
    return 0;
}




