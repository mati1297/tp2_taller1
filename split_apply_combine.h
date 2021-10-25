#ifndef TP2_TALLER1_SPLITAPPLYCOMBINE_H
#define TP2_TALLER1_SPLITAPPLYCOMBINE_H

#include <string>
#include <thread>
#include <vector>
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"
#include "protected_results_vector.h"
#include "worker.h"

// Clase que ejecuta el programa.
class SplitApplyCombine {
    uint8_t workers;
    uint32_t part_columns;
    DataLoader data_loader;
    ToDoQueue queue;
    ProtectedResultsVector results_vector;
    std::vector<Worker> workers_vector;
    std::vector<std::thread> threads_vector;


    /* Metodo privado que agrega tokens de finalizacion a la cola
     * y espera a los threads. */
    void endAndJoin();

    // Metodo que imprime resultados.
    void printResults();

    /* Metodo que valida que el texto ingresado corresponda a un numero positivo
     * y lo convierte a uint32_t. */
    static uint32_t validateAndConvert(const std::string &text);

public:
    /* Constructor.
    * recibe los parametros que se reciben
    * por linea de comandos, el nombre del dataset, la cantidad de columnas
    * y la cantidad de workers.
    * Pre:
            *      dataset_filename debe apuntar a una posicion de memoria valida. */
    SplitApplyCombine(const char *const dataset_filename,
                      const std::string &text_columns,
                      const std::string &text_workers);

    /* Metodo que ejecuta el programa, prepara los threads y sus workers,
    * prepara la cola y las tareas y luego imprime el resultado. */
    void execute();
};


#endif //TP2_TALLER1_SPLITAPPLYCOMBINE_H
