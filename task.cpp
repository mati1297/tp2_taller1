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

Task::Task(const uint32_t & part_columns):
        op(nullptr), part_columns(part_columns),
        part_rows(1), column_to_process(0),
        index_from(0), index_to(1) {}


void Task::loadQueue(ToDoQueue & queue, const size_t & result_idx) {
    // Si no se configuro el operador, se lanza excepcion.
    if (op == nullptr)
        throw std::invalid_argument("no hay un operador designado");


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


void Task::setOperator(const Operator * const & op) {
    this->op = op;
}

void Task::setRange(const uint32_t & from, const uint32_t & to) {
    if (to <= from)
        throw std::invalid_argument("la fila inicial es mayor que la final");
    index_from = from;
    index_to = to;
}

void Task::setColumnToProcess(const uint32_t & column) {
    if (column >= this->part_columns)
        throw std::invalid_argument("la columna ingresada no es valida");
    this->column_to_process = column;
}

void Task::setPartitionRows(const uint32_t & rows) {
    if (rows < 1)
        throw std::invalid_argument("la cantidad de columnas no puede ser 0");
    if (this->part_rows == rows)
        return;
    this->part_rows = rows;
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







