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
    DataPartition data_partition(0, rows, 4);
    Max max = Max(0, rows, 0, 15);
    Min min = Min(0, rows, 0, 15);
    Sum sum = Sum(0, rows, 1, 13);
    Operator * op = &min;
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
