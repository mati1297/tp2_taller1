#include <algorithm>
#include <vector>
#include "min.h"


void Min::operate(Result & result, const std::vector<uint16_t>& data,
                  const uint32_t & from, const uint32_t & to) const {
    uint16_t minimum = UINT16_MAX;
    for (uint32_t i = from; i < to; i++){
        minimum = std::min(minimum, data[i]);
    }
    result.setNumber(minimum);
}



