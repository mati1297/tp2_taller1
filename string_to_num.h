#ifndef TP2_TALLER1_STRINGTONUM_H
#define TP2_TALLER1_STRINGTONUM_H

#include <cstdint>
#include <string>
#include <stdexcept>


/* Clase estatica que provee metodos para conversion de string a variables
 * numericas. */
class StringToNum {
private:
    /* Constructor por defecto, se coloca como privado para que la
     * clase no sea instanciable. */
    StringToNum();

public:
    // Metodo que permite convertir string a uint32_t.
    static uint32_t stou32(const std::string & str);

    // Metodo que permite convertir string a uint8_t.
    static uint8_t stou8(const std::string & str);
};


#endif //TP2_TALLER1_STRINGTONUM_H
