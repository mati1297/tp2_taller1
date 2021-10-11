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
    Result * const result;
    std::vector<DataPartition> * const data_partitions;
    const Operator * const op;
    const uint32_t column_to_process;


public:
    /* Constructor.
     * Pre:
     *      queue_ debe apuntar a un objeto ToDoQueue valida.
     *      data_loader debe apuntar a un objeto DataLoader valido.
     *      result_ debe apuntar a un objeto Result valido.
     *      data_partitions_ debe apuntar a un objeto
     *          std::vector<DataPartition> valido.
     *      operator_ debe apuntar a un objeto Operator valido. */
    Worker(ToDoQueue * const & queue_, DataLoader * const & data_loader_,
           Result * const & result_,
           std::vector<DataPartition> * const & data_partitions_,
           const Operator * const & operator_, const uint32_t & col_to_process);

    // Operador (), ya que Worker es un functor, este debe ser poder llamado.
    void operator()();

    /* Metodo que realiza todas las acciones del Worker, y por consiguiente
     * del hilo. */
    void run() const;
};


#endif //TP2_TALLER1_WORKER_H
