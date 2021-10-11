#include "string_to_num.h"

#include <cstdint>
#include <string>
#include <stdexcept>

StringToNum::StringToNum() {}

uint32_t StringToNum::stou32(const std::string & str) {
    uint32_t var = 0;
    // Se chequea que no comience la cadena con un signo menos.
    if (str.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");
    try {
        size_t pos;
        // Se convierte a una variable de tipo automatico.
        auto temp = std::stoull(str, &pos, 10);
        /* Se chequea que se haya podido convertir la totalidad de la cadena
         * y si no es asi se lanza una excepcion. */
        if (pos != str.length())
            throw std::invalid_argument("otros caracteres ademas de numeros");
        // Si el valor ocupa mas que 32 bits se lanza excepcion.
        if (temp > UINT32_MAX)
            throw std::out_of_range("numero de mas de 32 bits");
        var = static_cast<uint32_t>(temp);
    }
    // Se atrapan todas las posibles excepciones.
    catch(std::exception & e) {
        throw;
    }
    return var;
}

uint8_t StringToNum::stou8(const std::string & str) {
    uint32_t var = 0;
    // Se chequea que no comience la cadena con un signo menos.
    if (str.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");
    try {
        size_t pos;
        // Se convierte a una variable de tipo automatico.
        auto temp = std::stoull(str, &pos, 10);
        /* Se chequea que se haya podido convertir la totalidad de la cadena
         * y si no es asi se lanza una excepcion. */
        if (pos != str.length())
            throw std::invalid_argument("otros caracteres ademas de numeros");
        // Si el valor ocupa mas que 8 bits se lanza excepcion.
        if (temp > UINT8_MAX)
            throw std::out_of_range("numero de mas de 8 bits");
        var = static_cast<uint8_t>(temp);
    }
    // Se atrapan todas las posibles excepciones.
    catch(std::exception & e) {
        throw;
    }
    return var;
}
