#ifndef TP2_TALLER1_MAX_H
#define TP2_TALLER1_MAX_H

#include <vector>
#include <cstdint>
#include "operator.h"

/* Clase que representa la operacion maximo, es heredera
 * de la clase Operator. */
class Max: public Operator {
    // Metodo que devuelve el valor neutral de la operacion.
    uint16_t getNeutralValue() const override;

public:
    /* Metodo que acumula segun la operacion en accumulator el resultado
     * de operar a este y a number. */
    void accumulate(uint16_t & accumulator,
                    const uint16_t & number) const override;
};


#endif //TP2_TALLER1_MAX_H
