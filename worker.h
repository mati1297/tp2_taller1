#ifndef TP2_TALLER1_WORKER_H
#define TP2_TALLER1_WORKER_H

#include <vector>
#include "result.h"
#include "to_do_queue.h"
#include "data_loader.h"
#include "sum.h"

/* Clase (Functor) que se encarga de ejecutar las acciones de los
 * distintos hilos del programa. Posee variables y punteros a
 * los objetos que el hilo debe utilizar para funcionar. */
class Worker {
    ToDoQueue * const queue;
    DataLoader * const data_loader;
    std::vector <Result> * const results;
    DataPartition data_partition;


public:
    Worker(ToDoQueue *const &queue_, DataLoader *const &data_loader_, std::vector<Result> *const &results_,
           const uint32_t &part_columns);


    // Operador (), ya que Worker es un functor, este debe ser poder llamado.
    void operator()();

    /* Metodo que realiza todas las acciones del Worker, y por consiguiente
     * del hilo. */
    void run();
};


#endif //TP2_TALLER1_WORKER_H
