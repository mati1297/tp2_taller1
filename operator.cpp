#include <cstdint>
#include <vector>
#include "operator.h"

uint16_t Operator::operate(const std::vector<uint16_t>& data) const{
    return operate(data, 0, data.size());
}