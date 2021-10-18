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
        op(op_), part_columns((part_columns_ > 0) ? part_columns_ : 1),
        part_rows((part_rows_ > 0) ? part_rows_ : 1),
        column_to_process((col_to_proc < part_columns) ? col_to_proc : 0),
        index_from(from), index_to((to >= index_from) ? to : index_from) {}


void Task::loadQueue(ToDoQueue & queue, const size_t & result_idx) {
    // Se itera tantas veces como particiones haya.
    for (uint32_t j = 0; j < ceil(index_to - index_from, part_rows); j++){
        // Se calculan valores inicial y final en terminos de numeros a leer.
        uint32_t from = (index_from + j * part_rows) * part_columns;
        uint32_t to = (index_from + (j+1) * part_rows) * part_columns;
        if (to > index_to * part_columns)
            to = index_to * part_columns;

        // Se arma el token y se pushea a la cola.
        queue.push(ToDoToken(false, op, result_idx, part_rows,
                             from, to, column_to_process));
    }
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







