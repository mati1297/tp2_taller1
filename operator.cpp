#include <cstdint>
#include <vector>
#include <iostream>
#include "operator.h"
#include "result.h"
#include "data_partition.h"

void Operator::accumulate(Result & accumulator,
                          Result & new_result) const {
    // Se llama a la funcion accumulate del objeto accumulator.
    accumulator.accumulate(new_result, this);
}

void Operator::operateData(Result & result, const DataPartition & data,
                           const uint32_t & column_to_op) const {
    /* Primeramente se carga en el acumulador el
     * valor neutral de la operacion. */
    uint16_t accumulator = getNeutralValue();
    // Se obtiene la columna correspondiente en forma de vector.
    const std::vector<uint16_t> & col_data =
                data.getColumnData(column_to_op);
    // Se acumula todos los valores en la columna.
    for (uint32_t i = 0; i < col_data.size(); i++){
        accumulate(accumulator, col_data[i]);
    }
    // Se setea el valor en result.
    result.setNumber(accumulator);
}

void Operator::accumulateExtra(uint32_t & accumulator,
                               const uint32_t &number) const {
    // Por defecto, el acumulador de extra no acumula nada.
    accumulator = 0;
}

void Operator::printResult(Result & result) const {
    // Por defecto, solo se imprime el numero del resultado.
    std::cout << result.getNumber() << std::endl;
}



