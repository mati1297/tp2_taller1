//
// Created by matias on 3/10/21.
//

#ifndef TP2_TALLER1_MAX_H
#define TP2_TALLER1_MAX_H

#include <cstdint>
#include "operator.h"

class Max: public Operator {
public:
    uint16_t operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const override;
};


#endif //TP2_TALLER1_MAX_H
