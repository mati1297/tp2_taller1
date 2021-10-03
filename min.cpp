#include "min.h"


min::min(size_t column, size_t rows, size_t index_from, size_t index_to) : (column, rows, index_from, index_to) {}

uint16_t min::operate(const std::vector<uint16_t> &data, const size_t& from, const size_t& to) const  {
    uint16_t minimum = UINT16_MAX;
    for (size_t i = from; i < to; i++){
        minimum = std::min(minimum, data[i]);
    }
    return minimum;
}



