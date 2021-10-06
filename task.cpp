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
        fake_index_to(index_to - index_from),
        results(ceil(index_to - index_from, part_rows)),
        partitions(workers, DataPartition(0, part_rows, part_columns)),
        data_loader(data_loader), current_data_partition_index(0) {}

void Task::reset(){
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
    fake_index_to = index_to - index_from;
    current_data_partition_index = 0;
    for (Result & result : results)
        result.reset();
}

Result Task::run() {
    reset();
    try {
        while (!data_loader->endOfDataset()) {
            uint32_t index = split();
            apply(partitions[index]);
        }
    }
    catch(std::exception& e){
        throw;
    }
    Result result = combine();
    op->printResult(result);
    return result;
}

uint32_t Task::split() {
    uint32_t reduced_index = current_data_partition_index % workers;
    try {
        data_loader->load(partitions[reduced_index],
                          current_data_partition_index);
    }
    catch(std::length_error& e){
        throw;
    }
    current_data_partition_index++;
    return reduced_index;
}

//revisarlo esto, ver tema de si se puede hacer sin ir a negativo.
void Task::apply(const DataPartition & dp){
    if(op == nullptr)
        throw std::invalid_argument("no hay un operador designado");
    int64_t dp_from = std::max((uint32_t) 0,
                           dp.getFirstRowIndex()) - dp.getFirstRowIndex();
    int64_t dp_to = std::min(fake_index_to - 1,
                         dp.getLastRowIndex()) - dp.getFirstRowIndex() + 1;
    if (dp_to > dp_from){
        uint32_t idx = dp.getIndex();
        try {
            const std::vector<uint16_t> &column_data =
                    dp.getColumnData(column_to_process);
            op->operate(results[idx],
                        column_data, dp_from, dp_to);
        }
        catch(std::invalid_argument& e) {
            throw;
        }
    }
}

Result Task::combine() const {
    Result result;
    op->operate(result, results);
    return result;
}

void Task::setOperator(const Operator * const & op) {
    this->op = op;
}

void Task::setRange(const uint32_t & from, const uint32_t & to) {
    if (to <= from)
        throw std::invalid_argument("la fila inicial es mayor que la final");
    if ((index_to - index_from) != (to - from))
        results = std::vector<Result>(
                ceil(to - from, part_rows));
    index_from = from;
    index_to = to;
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
    fake_index_to = index_to - index_from;
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
    results = std::vector<Result>(
            ceil(index_to - index_from, part_rows));
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







