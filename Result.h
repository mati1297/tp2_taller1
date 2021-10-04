//
// Created by matias on 4/10/21.
//

#ifndef TP2_TALLER1_RESULT_H
#define TP2_TALLER1_RESULT_H


#include <cstdint>
#include <cstddef>

class Result {
    uint16_t number;
    size_t extra;

public:
    Result();
    explicit Result(uint16_t number);
    Result(uint16_t number, size_t extra);
    void setNumber(uint16_t number);
    void setExtra(size_t extra);

    const uint16_t &getNumber() const;

    const size_t &getExtra() const;
};


#endif //TP2_TALLER1_RESULT_H
