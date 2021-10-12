#include <vector>
#include "worker.h"
#include "to_do_token.h"
#include "sum.h"


Worker::Worker(ToDoQueue & queue_, DataLoader & data_loader_,
               std::vector<Result> & results_,
               const uint32_t & part_columns): queue(queue_),
               data_loader(data_loader_), results(results_),
               data_partition(0, part_columns) {}


void Worker::operator()() {
    // Se llama al metodo run
    run();
}

void Worker::run() {
    /* Se realiza un while infinito hasta que salga mediante
     * la llegada de un token que indique la finalizacion. */
    while (true) {
        ToDoToken to_do_token;
        // Si la cola no esta vacia se saca un token.
        bool queue_not_empty = queue.ifNotEmptyPop(to_do_token);
        // Si esta vacia se vuelve a comenzar el ciclo.
        if (!queue_not_empty)
            continue;
        // Si el token indica el fin del trabajo, se rompe el ciclo.
        if (to_do_token.endOfWork())
            break;

        // Se obtiene la cantidad de filas que debe tener la particion.
        uint32_t part_rows = to_do_token.getPartitionRows();

        /* Se modifica la cantida de filas por particion
         * (si es la misma no cambia por como esta hecho el metodo). */
        data_partition.setRows(part_rows);

        // Se cargan los demas datos del token.
        uint32_t from = to_do_token.getFrom();
        uint32_t to = to_do_token.getTo();
        uint32_t column_to_process = to_do_token.getColumnToProcess();
        const size_t result_idx = to_do_token.getResultIndex();
        const Operator * op = to_do_token.getOperator();

        // Se carga la particion.
        data_loader.load(data_partition, from, to);
        /* Si la particion no se cerro es que no se leyo. Se vuelve
         * al principio. */
        if (!data_partition.isClosed())
            continue;

        /* Se prepara un resultado temporal y se le pasa al metodo accumulate
         * del operador. */
        Result temp_result;
        if (!op)
            return;
        op->operateData(temp_result, data_partition,
                        column_to_process);
        // Se opera acumulativamente y se guarda en el resultado compartido.
        op->accumulate(results[result_idx], temp_result);
    }
}



