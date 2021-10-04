//
// Created by matias on 3/10/21.
//

#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H
#include <vector>


class Operator {

public:
    virtual uint16_t operate(const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const = 0;

    uint16_t operate(const std::vector<uint16_t> &data) const;
};


#endif //TP2_TALLER1_OPERATOR_H
