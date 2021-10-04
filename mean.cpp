#include <vector>
#include <iostream>
#include "mean.h"

void Mean::operate(Result &result, const std::vector<uint16_t> &data,
                   const size_t &from, const size_t &to) const {
    uint16_t sum = 0;
    for (size_t i = from; i < to; i++)
        sum += data[i];
    result.setNumber(sum);
    result.setExtra(to - from);
}

void Mean::operate(Result &result, const std::vector<Result> &data) const {
    Operator::operate(result, data);
    size_t total_extra = 0;
    for (Result result_ : data)
        total_extra += result_.getExtra();
    result.setExtra(total_extra);
}

void Mean::printResult(Result &result) const {
    std::cout << result.getNumber() << '/' << result.getExtra() << std::endl;
}
