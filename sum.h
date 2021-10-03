//
// Created by matias on 2/10/21.
//

#ifndef TP2_TALLER1_SUM_H
#define TP2_TALLER1_SUM_H


#include <cstdint>
#include "operator.h"

class sum: public  {
public:
    sum(size_t column, size_t rows, size_t index_from, size_t index_to);
    uint16_t operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const override;
};


#endif //TP2_TALLER1_SUM_H
