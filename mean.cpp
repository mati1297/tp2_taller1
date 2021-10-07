#include <vector>
#include <iostream>
#include "mean.h"
#include "result.h"

void Mean::operate(Result & accumulator,
                       Result & new_result) const {
    Operator::operate(accumulator, new_result);
    uint32_t acc = accumulator.getExtra();
    acc += new_result.getExtra();
    accumulator.setExtra(acc);
}

void Mean::operate(Result & result, const std::vector<uint16_t> & data) const {
    Operator::operate(result, data);
    result.setExtra(data.size());
}


void Mean::printResult(Result & result) const {
    std::cout << result.getNumber() << '/' << result.getExtra() << std::endl;
}
