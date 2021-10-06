//
// Created by matias on 3/10/21.
//

#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H
#include <vector>
#include "result.h"


class Operator {
public:
    virtual void operate(Result & result, const std::vector<uint16_t> & data,
                         const uint32_t & from, const uint32_t & to) const = 0;
    void operate(Result & result, const std::vector<uint16_t> & data) const;
    virtual void operate(Result & result,
                         const std::vector<Result> & data) const;
    virtual void printResult(Result & result) const;
};


#endif //TP2_TALLER1_OPERATOR_H
