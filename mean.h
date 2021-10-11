#ifndef TP2_TALLER1_MEAN_H
#define TP2_TALLER1_MEAN_H


#include <cstddef>
#include <cstdint>
#include <vector>
#include "result.h"
#include "operator.h"
#include "sum.h"


class Mean: public Sum {
public:
    void operate(Result & accumulator,
                           Result & new_result) const override;

    void operate(Result &result, const DataPartition &data,
                 const uint32_t &column_to_op) const override;

    void printResult(Result & result) const override;

    void operateExtra(uint32_t & accumulator,
                      const uint32_t &number) const override;
};


#endif //TP2_TALLER1_MEAN_H
