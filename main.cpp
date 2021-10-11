#include <iostream>
#include "file_reader.h"
#include "data_loader.h"
#include "data_partition.h"
#include "task.h"
#include "task_reader.h"

int main(int argc, char * argv[]) {
    if (argc < 4)
        return 1;

    
    FileReader file_reader;

    try {
        file_reader.open(argv[1]);
    }
    catch(std::exception & e) {
        std::cerr << "Error al leer el archivo: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    uint32_t columns = std::stoul(argv[2]);
    uint32_t workers = std::stoul(argv[3]);

    DataLoader data_loader(file_reader);
    Task task(columns, workers, &data_loader);

    TaskReader task_reader;

    while (!std::cin.eof() && std::cin.peek() != EOF) {
        try {
            if (task_reader.read(task))
                break;
        }
        catch(std::exception &e) {
            std::cerr << "Error al leer la tarea: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        try {
            task.run();
        }
        catch(std::exception &e){
            std::cerr << "Error al correr la tarea: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }

    return 0;
}
