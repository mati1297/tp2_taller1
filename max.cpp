#include <vector>
#include <algorithm>
#include "max.h"


void Max::operate(Result& result, const std::vector<uint16_t>& data,
                  const size_t& from, const size_t& to) const {
    uint16_t maximum = 0;
    for (size_t i = from; i < to; i++){
        maximum = std::max(maximum, data[i]);
    }
    result.setNumber(maximum);
}




