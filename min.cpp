#include "min.h"

uint16_t Min::operate(const std::vector<uint16_t> &data, const size_t& from, const size_t& to) const  {
    uint16_t minimum = UINT16_MAX;
    for (size_t i = from; i < to; i++){
        minimum = std::min(minimum, data[i]);
    }
    return minimum;
}



