#ifndef TP2_TALLER1_SUM_H
#define TP2_TALLER1_SUM_H

#include <vector>
#include <cstdint>
#include "operator.h"

class Sum: public Operator{
    uint16_t getNeutralValue() const override;
public:
    void operate(uint16_t &accumulator, const uint16_t &number) const override;


};


#endif //TP2_TALLER1_SUM_H
