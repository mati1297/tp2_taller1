#include <iostream>
#include "file_reader.h"
#include "data_loader.h"
#include "data_partition.h"
#include "task.h"
#include "task_reader.h"
#include "sum.h"
#include "min.h"
#include "max.h"

int main(int argc, char * argv[]) {
    if(argc < 4)
        return 1;

    FileReader file_reader(argv[1]);

    size_t columns = std::stoull(argv[2]);
    size_t workers = std::stoull(argv[3]);

    size_t rows = 2;
    Min min = Min();
    Operator * op = &min;
    DataLoader data_loader = DataLoader(&file_reader);
    Task task = Task(op, columns, rows, 0, 0, 1, workers, &data_loader);

    TaskReader task_reader = TaskReader();

    while (!std::cin.eof() && std::cin.peek() != EOF) {
        try {
            if(task_reader.read(task))
                break;
        }
        catch (std::exception &e) {
            return EXIT_FAILURE;
        }
        task.run();
    }

    return 0;
}
