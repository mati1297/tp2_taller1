#include <vector>
#include <iostream>
#include "mean.h"
#include "result.h"
#include "operator.h"

void Mean::operate(Result & accumulator,
                       Result & new_result) const {
    Operator::operate(accumulator, new_result);
}

void Mean::operate(Result & result, const DataPartition & data, const uint32_t & column_to_op) const {
    Operator::operate(result, data, column_to_op);
    result.setExtra(data.getRows());
}

void Mean::operateExtra(uint32_t & accumulator, const uint32_t & number) const {
    accumulator += number;
}

void Mean::printResult(Result & result) const {
    std::cout << result.getNumber() << '/' << result.getExtra() << std::endl;
}
