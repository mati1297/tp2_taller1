#include <cstdint>
#include <vector>
#include <algorithm>
#include "task.h"
#include "data_partition.h"
#include "operator.h"

Task::Task(const uint32_t & part_columns, const uint32_t & workers,
           DataLoader * const & data_loader):
        op(nullptr), workers(workers), part_columns(part_columns),
        part_rows(1), column_to_process(0),
        index_from(0), index_to(1),
        result(), partitions(workers,
                             DataPartition(0, part_rows, part_columns)),
        data_loader(data_loader) {}

void Task::reset(){
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
    result.reset();
}

Result Task::run() {
    reset();
    try {
        while (!data_loader->endOfDataset()) {
            split();
            apply(partitions[0]); //hardcoded para 1 worker
        }
    }
    catch(std::exception& e){
        throw;
    }
    op->printResult(result);
    return result;
}

void Task::split() {
    try {
        data_loader->load(partitions[0]); //hardcoded para 1 worker
    }
    catch(std::length_error& e){
        throw;
    }
}

//revisarlo esto, ver tema de si se puede hacer sin ir a negativo.
void Task::apply(const DataPartition & dp){
    if (op == nullptr)
        throw std::invalid_argument("no hay un operador designado");
    try {
        Result temp_result;
        op->operate(temp_result, dp, column_to_process);
        op->operate(result, temp_result);
    }
    catch(std::invalid_argument& e) {
        throw;
    }
}

//Result Task::combine() const {
//    Result result;
//    op->operate(result, results);
//    return result;
//}

void Task::setOperator(const Operator * const & op) {
    this->op = op;
}

void Task::setRange(const uint32_t & from, const uint32_t & to) {
    if (to <= from)
        throw std::invalid_argument("la fila inicial es mayor que la final");
    index_from = from;
    index_to = to;
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
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
    for (uint32_t i = 0; i < workers; i++){
        partitions[i].setRows(rows);
    }
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







