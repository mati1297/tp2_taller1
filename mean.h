//
// Created by matias on 4/10/21.
//

#ifndef TP2_TALLER1_MEAN_H
#define TP2_TALLER1_MEAN_H


#include <cstddef>
#include <cstdint>
#include <vector>
#include "Result.h"
#include "operator.h"

class Mean: public Operator {
public:
    void operate(Result& result, const std::vector<uint16_t>& data, const size_t& from, const size_t& to) const override;

    void operate(Result& result, const std::vector<Result> & data) const override;

    virtual void printResult(Result& result) const;
};


#endif //TP2_TALLER1_MEAN_H
