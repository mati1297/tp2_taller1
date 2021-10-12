#include "split_apply_combine.h"
#include <string>
#include <vector>
#include <iostream>
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"
#include "string_to_num.h"


SplitApplyCombine::SplitApplyCombine(): data_loader() {}

void SplitApplyCombine::execute(const char * const dataset_filename,
                         const std::string & text_columns,
                         const std::string & text_workers) {
    uint32_t columns = 0;
    uint8_t workers = 0;

    /* Se validan los datos ingresados, se abre el archivo, y se convierten
     * a datos numericos las columnas y workers. */
    try {
        loadAndValidate(dataset_filename, text_columns,
                        text_workers, columns, workers);
    }
    catch(std::exception & e) {
        throw;
    }

    // Se crea la task, el TaskReader y el vector de resultados.
    Task task(columns, workers, &data_loader);

    TaskReader task_reader;

    std::vector<Result> results(0);

    // Se realiza un loop infinito hasta que termine la entrada.
    while (true) {
        // Se lee la entrada y se carga en la task.
        try {
            if (task_reader.read(task))
                break;
        }
        catch(std::exception &e) {
            std::string msg = e.what();
            throw std::invalid_argument("Error al leer la tarea: " + msg);
        }
        /* Se ejecuta la tarea y se guarda el resultado en el vector
         * de resultados. */
        try {
            results.push_back(task.run());
        }
        catch(std::exception &e){
            std::string msg = e.what();
            throw std::invalid_argument("Error al correr la tarea: " + msg);
        }
    }

    // Se imprimen los resultados.
    for (size_t i = 0; i < results.size(); i++){
        std::cout << results[i] << std::endl;
    }
}


void SplitApplyCombine::loadAndValidate(const char * const dataset_filename,
                     const std::string & text_columns,
                     const std::string & text_workers,
                     uint32_t & columns, uint8_t & workers) {
    try {
        data_loader.openFile(dataset_filename);
    }
    catch(std::exception & e) {
        std::string msg = e.what();
        throw std::invalid_argument("Error al abrir el archivo: " + msg);
    }

    try {
        columns = StringToNum::stou32(text_columns);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("Error al leer las columnas: " + msg);
    }

    try {
        workers = StringToNum::stou8(text_workers);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("Error al leer la fila inicial: " + msg);
    }
}
