#ifndef TP2_TALLER1_MAX_H
#define TP2_TALLER1_MAX_H

#include <vector>
#include <cstdint>
#include "operator.h"

class Max: public Operator {
    uint16_t getNeutralValue() const override;

public:
    void operate(uint16_t & accumulator,
                 const uint16_t & number) const override;
};


#endif //TP2_TALLER1_MAX_H
