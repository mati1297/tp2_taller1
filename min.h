#ifndef TP2_TALLER1_MIN_H
#define TP2_TALLER1_MIN_H

#include <vector>
#include <cstdint>
#include "operator.h"

class Min: public Operator {
    uint16_t getNeutralValue() const override;

public:
    void operate(uint16_t &accumulator, const uint16_t &number) const override;
};


#endif //TP2_TALLER1_MIN_H
