#ifndef TP2_TALLER1_MEAN_H
#define TP2_TALLER1_MEAN_H


#include <cstddef>
#include <cstdint>
#include <vector>
#include "result.h"
#include "operator.h"

class Mean: public Operator {
public:
    void operate(Result & result, const std::vector<uint16_t> & data,
                 const uint32_t & from, const uint32_t & to) const override;

    void operate(Result & result,
                 const std::vector<Result> & data) const override;

    virtual void printResult(Result & result) const override;
};


#endif //TP2_TALLER1_MEAN_H
