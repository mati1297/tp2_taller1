#ifndef TP2_TALLER1_RESULT_H
#define TP2_TALLER1_RESULT_H


#include <cstdint>
#include <cstddef>
#include <mutex>
#include "operator.h"

class Operator;

class Result {
    uint16_t number;
    uint32_t extra;
    bool initialized;
    std::mutex mutex;


public:
    Result();
    Result(const Result & orig);
    void setNumber(const uint16_t & number_);
    void setExtra(const uint32_t & extra_);

    const uint16_t & getNumber() const;

    const uint32_t & getExtra() const;

    void reset();

    void accumulate(const uint16_t & number_, const uint32_t & extra_, const Operator * const & op);

    void accumulate(const Result &result_, const Operator * const & op);
};


#endif //TP2_TALLER1_RESULT_H
