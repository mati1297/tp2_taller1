#include <vector>
#include <iostream>
#include "mean.h"
#include "result.h"
#include "operator.h"

void Mean::operateData(Result & result, const DataPartition & data,
                       const uint32_t & column_to_op) const {
    // Se opera igual que en cualquier Operator.
    Operator::operateData(result, data, column_to_op);
    // Luego, se setea el atributo extra como el total de filas procesadas.
    result.setExtra(data.getRows());
}

void Mean::accumulateExtra(uint32_t & accumulator, const uint32_t & number) const {
    // El extra se acumula como la suma de los extras.
    accumulator += number;
}

void Mean::printResult(Result & result) const {
    // Se imprime el resultado y aparte el extra tras una barra.
    std::cout << result.getNumber() << '/' << result.getExtra() << std::endl;
}
