#include <iostream>
#include "file_reader.h"
#include "data_partition.h"
#include "operator.h"
#include "sum.h"
#include "min.h"
#include "max.h"

int main() {
    file_reader file_reader("dataset");
    uint16_t number;

    size_t rows = 2;
    data_partition data_partition(0, rows, 4);
    max max = max(0, rows, 0, 15);
    min min = min(0, rows, 0, 15);
    sum sum = sum(0, rows, 1, 13);
     * op = &min;
    int i = 0;
    while (!file_reader.eof()){
        data_partition.reset(i);
        while (!data_partition.isFull()){
            file_reader.read(number);
            data_partition.load(number);
        }
        data_partition.print();
        op->apply(data_partition);
        i++;
    }

    uint16_t result = op->combine();

    std::cout << "Filas: " << i << std::endl;
    std::cout << "Resultado: " << result << std::endl;

    return 0;
}
