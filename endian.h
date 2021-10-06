//
// Created by matias on 6/10/21.
//

#ifndef TP2_TALLER1_ENDIAN_H
#define TP2_TALLER1_ENDIAN_H

#include <cstdint>

#define MASK 255;

class Endian {
    static bool nativeIsLittleEndian();

    Endian() = default;

public:
    static uint16_t change(const uint16_t &number);

    static uint16_t toNative(const uint16_t &number, bool is_little);
};


#endif //TP2_TALLER1_ENDIAN_H
