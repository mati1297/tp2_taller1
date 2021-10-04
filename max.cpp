#include "max.h"

uint16_t Max::operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const {
    uint16_t maximum = 0;
    for (size_t i = from; i < to; i++){
        maximum = std::max(maximum, data[i]);
    }
    return maximum;
}



