#ifndef TP2_TALLER1_SPLITAPPLYCOMBINE_H
#define TP2_TALLER1_SPLITAPPLYCOMBINE_H

#include <string>
#include <thread>
#include <vector>
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"
#include "protected_results_vector.h"

// Clase que ejecuta el programa.
class SplitApplyCombine {
    /* Metodo privado que valida los parametros que se le pasan
     * a la funcion execute y los convierte al tipo de dato
     * correspondiente. */
    void loadAndValidate(const std::string & text_columns,
                         const std::string & text_workers,
                         uint32_t & columns, uint8_t & workers);

    /* Metodo privado que agrega tokens de finalizacion a la cola
     * y espera a los threads. */
    void endAndJoin(const uint8_t &workers_cant,
                    std::vector<std::thread> &threads_vector,
                    ToDoQueue &queue);

    void printResults(ProtectedResultsVector &results);

public:
    // Constructor sin parametros.
    SplitApplyCombine() = default;

    /* Metodo que ejecuta el programa, recibe los parametros que se reciben
     * por linea de comandos, el nombre del dataset, la cantidad de columnas
     * y la cantidad de workers. Prepara los threads y sus workers,
     * prepara la cola y las tareas y luego imprime el resultado.
     * Pre:
     *      dataset_filename debe apuntar a una posicion de memoria valida. */
    void execute(const char * const dataset_filename,
                                    const std::string & text_columns,
                                    const std::string & text_workers);
};


#endif //TP2_TALLER1_SPLITAPPLYCOMBINE_H
