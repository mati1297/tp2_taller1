#include <vector>
#include "worker.h"
#include "to_do_token.h"
#include "sum.h"
#include "protected_results_vector.h"


Worker::Worker(ToDoQueue & queue_, ProtectedResultsVector & results_,
               const uint32_t & part_columns): queue(queue_),
               results(results_) {}


void Worker::operator()() {
    // Se llama al metodo run
    run();
}

void Worker::run() {
    /* Se realiza un while infinito hasta que salga mediante
     * la llegada de un token que indique la finalizacion. */
    while (true) {
        ToDoToken to_do_token = queue.pop();
        // Si el token indica el fin del trabajo, se rompe el ciclo.
        if (to_do_token.endOfWork())
            break;

        // Se cargan los demas datos del token.
        uint32_t column_to_process = to_do_token.getColumnToProcess();
        const size_t result_idx = to_do_token.getResultIndex();
        const Operator * op = to_do_token.getOperator();
        const DataPartition & data_partition = to_do_token.getDataPartition();

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



