#include "string_to_num.h"

#include <cstdint>
#include <string>
#include <stdexcept>

StringToNum::StringToNum() {}

uint32_t StringToNum::stou32(const std::string & str) {
    uint32_t var = 0;
    if (str.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");
    try {
        size_t pos;
        auto temp = std::stoull(str, &pos, 10);
        if (pos != str.length())
            throw std::invalid_argument("otros caracteres ademas de numeros");
        if (temp > UINT32_MAX)
            throw std::out_of_range("numero de mas de 32 bits");
        var = static_cast<uint32_t>(temp);
    }
    catch(std::exception & e) {
        throw;
    }
    return var;
}

uint8_t StringToNum::stou8(const std::string & str) {
    uint32_t var = 0;
    if (str.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");
    try {
        size_t pos;
        auto temp = std::stoull(str, &pos, 10);
        if (pos != str.length())
            throw std::invalid_argument("otros caracteres ademas de numeros");
        if (temp > UINT8_MAX)
            throw std::out_of_range("numero de mas de 8 bits");
        var = static_cast<uint8_t>(temp);
    }
    catch(std::exception & e) {
        throw;
    }
    return var;
}
