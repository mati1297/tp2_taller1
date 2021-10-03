#include "sum.h"

sum::sum(size_t column, size_t rows, size_t index_from, size_t index_to) : (column, rows, index_from, index_to) {}

uint16_t sum::operate(const std::vector<uint16_t> &data, const size_t& from, const size_t& to) const {
    uint16_t sum = 0;
    for (size_t i = from; i < to; i++)
        sum += data[i];
    return sum;
}


