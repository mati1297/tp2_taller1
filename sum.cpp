#include <vector>
#include "sum.h"



void Sum::operate(Result& result, const std::vector<uint16_t>& data,
                  const size_t& from, const size_t& to) const {
    uint16_t sum = 0;
    for (size_t i = from; i < to; i++)
        sum += data[i];
    result.setNumber(sum);
}


