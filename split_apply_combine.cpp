#include "split_apply_combine.h"

#include "file_reader.h"
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"
#include "string_to_num.h"


SplitApplyCombine::SplitApplyCombine(): file_reader(), data_loader(file_reader) {}

void SplitApplyCombine::execute(const char * const dataset_filename,
                         const std::string & text_columns, const std::string & text_workers) {
    uint32_t columns = 0;
    uint8_t workers = 0;

    try {
        file_reader.open(dataset_filename);
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

    Task task(columns, workers, &data_loader);

    TaskReader task_reader;

    while (true) {
        try {
            if (task_reader.read(task))
                break;
        }
        catch(std::exception &e) {
            std::string msg = e.what();
            throw std::invalid_argument("Error al leer la tarea: " + msg);
        }
        try {
            task.run();
        }
        catch(std::exception &e){
            std::string msg = e.what();
            throw std::invalid_argument("Error al correr la tarea: " + msg);
        }
    }
}