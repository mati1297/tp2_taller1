#include <vector>
#include <iostream>
#include "mean.h"
#include "result.h"

void Mean::operate(Result & result, const std::vector<uint16_t> & data,
                   const uint32_t & from, const uint32_t & to) const {
    uint16_t sum = 0;
    for (uint32_t i = from; i < to; i++)
        sum += data[i];
    result.setNumber(sum);
    result.setExtra(to - from);
}

void Mean::operate(Result & result, const std::vector<Result> & data) const {
    Operator::operate(result, data);
    uint32_t total_extra = 0;
    for (uint32_t i = 0; i < data.size(); i++)
        total_extra += data[i].getExtra();
    result.setExtra(total_extra);
}

void Mean::printResult(Result & result) const {
    std::cout << result.getNumber() << '/' << result.getExtra() << std::endl;
}
