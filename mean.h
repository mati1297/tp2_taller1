#ifndef TP2_TALLER1_MEAN_H
#define TP2_TALLER1_MEAN_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include "result.h"
#include "operator.h"
#include "sum.h"

/* Clase que representa la operacion promedio, es heredera
 * de la clase Sum, ya que la operacion es similar. */
class Mean: public Sum {
public:
    /* Metodo que opera sobre la particion, acumulando los valores
     * de la columna correspondiente segun la operacion. Los resultados
     * son guardados en result. Se redefine el metodo definido en la
     * clase Operator.*/
    void operateData(Result &result, const DataPartition &data,
                     const uint32_t &column_to_op) const override;

    /* Metodo que acumula segun la operacion en accumulator el resultado
     * de operar a este y a number. Se redefine el metodo definido en la
     * clase Operator. */
    void accumulateExtra(uint32_t & accumulator,
                         const uint32_t &number) const override;

    /* Devuelve el separador de la operacion para impresion del resultado.
     * Sobrecarga el metodo de Operator.*/
    std::string getSeparator() const override;
};


#endif //TP2_TALLER1_MEAN_H
