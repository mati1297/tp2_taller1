#include <cstdint>
#include "endian.h"

bool Endian::nativeIsLittleEndian(){
    int num = 1;
    if (*(char *)&num == 1)
        return true;
    else
        return false;
}

uint16_t Endian::change(const uint16_t& number){
    char byte0 = (char) number & MASK;
    char byte1 = (number >> 8) &  MASK;
    return ((byte0  << 8) + byte1);
}

uint16_t Endian::toNative(const uint16_t& number, bool is_little){
    if (is_little xor nativeIsLittleEndian())
        return change(number);
    return number;
}

