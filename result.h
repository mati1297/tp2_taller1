#ifndef TP2_TALLER1_RESULT_H
#define TP2_TALLER1_RESULT_H


#include <cstdint>
#include <cstddef>

class Result {
    uint16_t number;
    uint32_t extra;
    bool initialized;

public:
    Result();
    explicit Result(const uint16_t & number);
    Result(const uint16_t & number, const uint32_t & extra);
    void setNumber(const uint16_t & number_);
    void setExtra(const uint32_t & extra_);

    const uint16_t & getNumber() const;

    const uint32_t & getExtra() const;

    void reset();

    const bool isInitialized() const;
};


#endif //TP2_TALLER1_RESULT_H
