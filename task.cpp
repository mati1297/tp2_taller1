#include <cstdint>
#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>
#include "task.h"
#include "data_partition.h"
#include "operator.h"
#include "to_do_queue.h"
#include "worker.h"

Task::Task(const uint32_t & part_columns_, const uint32_t & part_rows_,
           const Operator * op_, const uint32_t & from, const uint32_t & to,
           const uint32_t & col_to_proc):
        op(op_), part_columns(0), part_rows(0), column_to_process(0),
        index_from(from), index_to(0) {
    // Se validan los argumentos
    if (part_columns_ == 0)
        throw std::invalid_argument("la cantidad de columnas"
                                    " es menor o igual a 0");
    if (part_rows_ == 0)
        throw std::invalid_argument("la cantidad de filas es"
                                    " menor o igual a 0");
    if (col_to_proc >= part_columns_)
        throw std::invalid_argument("la columna que se pide"
                                    " procesar no existe");
    if (to < from)
        throw std::invalid_argument("el parametro hasta es "
                                    "menor que el desde");
    part_columns = part_columns_;
    part_rows = part_rows_;
    column_to_process = col_to_proc;
    index_to = to;
}


void Task::loadQueue(ToDoQueue & queue, DataLoader & data_loader,
                     const size_t & result_idx) {
    data_loader.setLimits(index_from * part_columns, index_to * part_columns);

    // Se itera tantas veces como particiones haya.
    for (uint32_t j = 0; j < ceil(index_to - index_from, part_rows); j++){
        DataPartition dp(part_rows, part_columns);

        data_loader.load(dp);

        // Se arma el token y se pushea a la cola.
        ToDoToken new_token(false, op, dp, result_idx, column_to_process);
        queue.push(new_token);
    }
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







