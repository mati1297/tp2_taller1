#ifndef TP2_TALLER1_STRINGTONUM_H
#define TP2_TALLER1_STRINGTONUM_H

#include <cstdint>
#include <string>
#include <stdexcept>

class StringToNum {
private:
    StringToNum();

public:
    static uint32_t stou32(const std::string & str);

    static uint8_t stou8(const std::string & str);
};


#endif //TP2_TALLER1_STRINGTONUM_H
