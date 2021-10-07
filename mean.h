#ifndef TP2_TALLER1_MEAN_H
#define TP2_TALLER1_MEAN_H


#include <cstddef>
#include <cstdint>
#include <vector>
#include "result.h"
#include "sum.h"

class Mean: public Sum {
public:
    void operate(Result & accumulator,
                           Result & new_result) const override;



    virtual void printResult(Result & result) const override;

    void operate(Result &result, const std::vector<uint16_t> &data) const override;
};


#endif //TP2_TALLER1_MEAN_H
