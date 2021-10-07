#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H
#include <vector>
#include "result.h"
#include "data_partition.h"

class Result;


class Operator {
protected:
    virtual uint16_t getNeutralValue() const = 0;

public:

    virtual void printResult(Result & result) const;

    virtual void operate(Result & result, const DataPartition & data,
                         const uint32_t & column_to_op) const;

    virtual void operate(Result &accumulator, Result &new_result) const;

    virtual void operate(uint16_t & accumulator, const uint16_t & number) const = 0;

    virtual void operateExtra(uint32_t & accumulator, const uint32_t & number) const;
};


#endif //TP2_TALLER1_OPERATOR_H
