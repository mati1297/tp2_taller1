#ifndef TP2_TALLER1_SPLITAPPLYCOMBINE_H
#define TP2_TALLER1_SPLITAPPLYCOMBINE_H

#include <string>
#include <thread>
#include <vector>
#include "file_reader.h"
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"

/* Clase que ejecuta el programa */
class SplitApplyCombine {
    DataLoader data_loader;

    /* Metodo privado que valida los parametros que se le pasan
     * a la funcion execute y los convierte al tipo de dato
     * correspondiente. */
    void loadAndValidate(const char * const dataset_filename,
                         const std::string & text_columns,
                         const std::string & text_workers,
                         uint32_t & columns, uint8_t & workers);

    void endAndJoin(const uint8_t &workers_cant,
                    std::vector<std::thread> &threads_vector,
                    ToDoQueue &queue);

public:
    // Constructor sin parametros.
    SplitApplyCombine();

    /* Metodo que ejecuta el programa, recibe los parametros que se reciben
     * por linea de comandos, el nombre del dataset, la cantidad de columnas
     * y la cantidad de workers.
     * Pre:
     *      dataset_filename debe apuntar a una posicion de memoria valida. */
    void execute(const char * const dataset_filename,
                                    const std::string & text_columns,
                                    const std::string & text_workers);
};


#endif //TP2_TALLER1_SPLITAPPLYCOMBINE_H
