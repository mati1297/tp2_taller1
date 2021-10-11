#include <cstdint>
#include <vector>
#include <iostream>
#include "operator.h"
#include "result.h"
#include "data_partition.h"

void Operator::operate(Result & accumulator,
                       Result & new_result) const {
    accumulator.accumulate(new_result, this);
}

void Operator::operate(Result & result, const DataPartition & data,
                       const uint32_t & column_to_op) const {
    uint16_t accumulator = getNeutralValue();
    const std::vector<uint16_t> & col_data =
                data.getColumnData(column_to_op);
    for (uint32_t i = 0; i < col_data.size(); i++){
        operate(accumulator, col_data[i]);
    }
    result.setNumber(accumulator);
}

void Operator::operateExtra(uint32_t & accumulator,
                            const uint32_t &number) const {
    accumulator = 0;
}

void Operator::printResult(Result & result) const {
    std::cout << result.getNumber() << std::endl;
}



