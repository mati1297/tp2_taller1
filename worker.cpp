#include <vector>
#include "worker.h"
#include "to_do_token.h"
#include "sum.h"

Worker::Worker(ToDoQueue *const &queue_, DataLoader *const &data_loader_,
               Result *const &result_,
               std::vector<DataPartition> *const &data_partitions_,
               const Operator *const &operator_,
               const uint32_t &col_to_process):
               queue(queue_), data_loader(data_loader_), result(result_),
               data_partitions(data_partitions_), op(operator_),
               column_to_process(col_to_process) {}

void Worker::operator()() {
    // Se llama al metodo run.
    run();
}

void Worker::run() const {
    /* Se realiza un while infinito hasta que salga mediante
     * la llegada de un token que indique la finalizacion. */
    while (true) {
        ToDoToken to_do_token;
        // Si la cola no esta vacia se saca un token.
        bool queue_not_empty = queue->ifNotEmptyPop(to_do_token);
        // Si esta vacia se vuelve a comenzar el ciclo.
        if (!queue_not_empty)
            continue;
        // Si el token indica el fin del trabajo, se rompe el ciclo.
        if (to_do_token.endOfWork())
            break;

        /* Se carga el indice de la particion que asigno el main thread
         * al worker */
        uint32_t part_index = to_do_token.getIndex();

        /* Si el dataset no termino, se cargan los datos en la particion.
         * Por el contrario, si termino, se continua. No se termina el ciclo
         * hasta que no se reciba el token que lo indique. */
        if (!data_loader->ifDatasetNotEndedLoad
                ((*data_partitions)[part_index])) {
            (*data_partitions)[part_index].setDone(true);
            continue;
        }

        /* Se prepara un resultado temporal y se le pasa al metodo accumulate
         * del operador. */
        Result temp_result;
        op->operateData(temp_result, (*data_partitions)[part_index],
                        column_to_process);
        // Se opera acumulativamente y se guarda en el resultado compartido.
        op->accumulate(*result, temp_result);

        // Se setea el flag done de la particion de datos como true.
        (*data_partitions)[part_index].setDone(true);
    }
}



