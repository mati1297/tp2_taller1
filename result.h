#ifndef TP2_TALLER1_RESULT_H
#define TP2_TALLER1_RESULT_H

#include <string>
#include <cstdint>
#include <cstddef>
#include <mutex>
#include "operator.h"

class Operator;

/* Clase protegida que representa un resultado de las distintas operaciones
 * del programa. Posee un atributo numero, usado por todas las
 * las operaciones, Y una atributo extra, que puede ser utilizado
 * para guardar un dato mas. Ademas posee un flag de inicializacion.
 * Es protegida ya que es accedida por los distintos hilos para guardar
 * el resultado parcial del calculo. */
class Result {
    uint16_t number;
    uint32_t extra;
    bool initialized;
    std::mutex mutex;
    std::string separator; // Separador de numero y extra en impresion.

public:
    // Constructor por sin parametros.
    Result();

    // Constructor por copia.
    Result(const Result & orig);

    // Permite setear el parametro numero.
    void setNumber(const uint16_t & number_);

    // Permite setear el parametro extra.
    void setExtra(const uint32_t & extra_);

    // Setea el separador que separa el numero del extra en la impresion.
    void setSeparator(const std::string & separator_);

    // Devuelve el atributo numero.
    const uint16_t & getNumber() const;

    // Devuelve el atributo extra.
    const uint32_t & getExtra() const;

    // Resetea sus atributos a 0 y el flag de inicializado a false.
    void reset();

    /* Acumula en si mismo el valor actual y el de number_ y extra segun
     * el operador que se le pase.
     * Pre:
     *      op debe apuntar a un objeto Operator valido. */
    void accumulate(const uint16_t & number_,
                    const uint32_t & extra_, const Operator * const & op);

    /* Acumula en si mismo el valor actual y el de result_ segun el operador
     * que se le pase.
     * Pre:
     *      op debe apuntar a un objeto Operator valido. */
    void accumulate(const Result &result_, const Operator * const & op);

    // Operador de output.
    friend std::ostream& operator<<(std::ostream& os, const Result & result);
};


#endif //TP2_TALLER1_RESULT_H
