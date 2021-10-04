//
// Created by matias on 2/10/21.
//

#ifndef TP2_TALLER1_SUM_H
#define TP2_TALLER1_SUM_H

#include <vector>
#include <cstdint>
#include "operator.h"

class Sum: public Operator{
public:
    void operate(Result& result, const std::vector<uint16_t>& data,
                 const size_t& from, const size_t& to) const override;
};


#endif //TP2_TALLER1_SUM_H
