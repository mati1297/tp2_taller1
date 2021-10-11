#ifndef TP2_TALLER1_OPERATOR_H
#define TP2_TALLER1_OPERATOR_H
#include <vector>
#include "result.h"
#include "data_partition.h"

class Result;

/* Clase abstracta que permite operar sobre particiones de
 * datos y resultados. No es posible instanciar esta clase
 * ya que hay metodos que deben ser definidos por sus clases
 * hijas. */
class Operator {
protected:
    // Devuelve el valor neutral de la operacion.
    virtual uint16_t getNeutralValue() const = 0;

public:
    /* Metodo que opera sobre la particion, acumulando los valores
     * de la columna correspondiente segun la operacion. Los resultados
     * son guardados en result. */
    virtual void operateData(Result & result, const DataPartition & data,
                             const uint32_t & column_to_op) const;

    /* Metodo que acumula en accumulator el resultado de operar a este y
     * a new_result. */
    virtual void accumulate(Result &accumulator, Result &new_result) const;

    /* Metodo que acumula segun la operacion en accumulator el resultado
     * de operar a este y a number. Debe ser implementado por las clases
     * herederas. */
    virtual void accumulate(uint16_t & accumulator,
                            const uint16_t & number) const = 0;

    /* Metodo que acumula segun la operacion en accumulator el resultado
     * de operar a este y a number. */
    virtual void accumulateExtra(uint32_t & accumulator,
                                 const uint32_t & number) const;

    // Formatea e imprime el resultado.
    virtual void printResult(Result & result) const;
};


#endif //TP2_TALLER1_OPERATOR_H
