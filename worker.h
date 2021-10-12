#ifndef TP2_TALLER1_WORKER_H
#define TP2_TALLER1_WORKER_H

#include <vector>
#include "result.h"
#include "to_do_queue.h"
#include "data_loader.h"
#include "sum.h"

/* Clase (Functor) que se encarga de ejecutar las acciones de los
 * distintos hilos del programa. Posee una particion de datos
 * y referencias a los objetos que necesita del programa. */
class Worker {
    ToDoQueue & queue;
    DataLoader & data_loader;
    std::vector <Result> & results;
    DataPartition data_partition;


public:
    /* Constructor, se le pasa la lista de to do, el data loader,
     * y la cantidad de columnas por particion. */
    Worker(ToDoQueue & queue_, DataLoader & data_loader_,
           std::vector<Result> & results_, const uint32_t &part_columns);

    // Operador (), ya que Worker es un functor, este debe ser poder llamado.
    void operator()();

    /* Metodo que realiza todas las acciones del Worker, y por consiguiente
     * del hilo. */
    void run();
};


#endif //TP2_TALLER1_WORKER_H
