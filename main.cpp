#include <iostream>
#include "file_reader.h"
#include "data_loader.h"
#include "data_partition.h"
#include "task.h"
#include "task_reader.h"
#include "sum.h"
#include "min.h"
#include "max.h"

int main() {
    FileReader file_reader("dataset");

    size_t rows = 2;
    Min min = Min();
    Operator * op = &min;
    DataLoader data_loader = DataLoader(&file_reader);
    Task task = Task(op, 4, rows, 0, 0, 15, 1, &data_loader);

    TaskReader task_reader = TaskReader();

    while(!std::cin.eof()) {
        task_reader.read(task);
        uint16_t result = task.run();
        std::cout << "Resultado: " << result << std::endl;
    }
    return 0;
}
