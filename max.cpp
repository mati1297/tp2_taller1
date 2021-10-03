#include "max.h"


max::max(size_t column, size_t rows, size_t index_from, size_t index_to) : (column, rows, index_from, index_to) {}

uint16_t max::operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const {
    uint16_t maximum = 0;
    for (size_t i = from; i < to; i++){
        maximum = std::max(maximum, data[i]);
    }
    return maximum;
}



