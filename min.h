#ifndef TP2_TALLER1_MIN_H
#define TP2_TALLER1_MIN_H

#include <vector>
#include <cstdint>
#include "operator.h"

class Min: public Operator {
public:
    void operate(Result & result, const std::vector<uint16_t> & data,
                 const uint32_t & from, const uint32_t & to) const override;
};


#endif //TP2_TALLER1_MIN_H
