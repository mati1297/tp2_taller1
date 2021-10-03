//
// Created by matias on 2/10/21.
//

#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H


#include <cstdint>
#include <vector>
#include "data_partition.h"

class Operator {
private:
    const size_t column;
    const size_t rows;
    const size_t index_from;
    const size_t index_to;
    std::vector<uint16_t> results;


public:
    Operator(size_t column, size_t rows, size_t index_from, size_t index_to);
    uint16_t operate(const std::vector<uint16_t>& data) const;
    virtual uint16_t operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const = 0;

    void apply(DataPartition &dp);

    uint16_t combine() const;
};


#endif //TP2_TALLER1_OPERATOR_H
