#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H
#include <vector>
#include "result.h"


class Operator {
protected:
    virtual uint16_t getNeutralValue() const = 0;

public:

    virtual void printResult(Result & result) const;

    virtual void operate(Result &result, const std::vector<uint16_t> &data) const;

    virtual void operate(Result &accumulator, Result &new_result) const;

    virtual void operate(uint16_t & accumulator, const uint16_t & number) const = 0;
};


#endif //TP2_TALLER1_OPERATOR_H
