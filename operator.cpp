#include <cstdint>
#include <vector>
#include <iostream>
#include "operator.h"
#include "result.h"
#include "data_partition.h"

void Operator::operate(Result & accumulator,
                       Result & new_result) const {
    if(!accumulator.isInitialized())
        accumulator.setNumber(new_result.getNumber());
    else {
        uint16_t acc = accumulator.getNumber();
        operate(acc, new_result.getNumber());
        accumulator.setNumber(acc);
    }
}

void Operator::operate(Result & result, const std::vector<uint16_t> & data) const {
    uint16_t accumulator = getNeutralValue();
    for (uint32_t i = 0; i < data.size(); i++){
        operate(accumulator, data[i]);
    }
    result.setNumber(accumulator);
}

void Operator::printResult(Result & result) const {
    std::cout << result.getNumber() << std::endl;
}
