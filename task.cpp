//
// Created by matias on 2/10/21.
//

#include <iostream>
#include <cmath>
#include "task.h"
#include "data_partition.h"
#include "operator.h"
#include "file_reader.h"

Task::Task(Operator * op, size_t partition_columns, size_t partition_rows, size_t column_to_process, size_t index_from, size_t index_to, size_t workers, DataLoader * data_loader): op(op), workers(workers), partition_columns(partition_columns), partition_rows(partition_rows), column_to_process(column_to_process), index_from(index_from), index_to(index_to), results(std::ceil((double(index_to) - double(index_from)) / 2)), partitions(workers, DataPartition(0, partition_rows, partition_columns)), data_loader(data_loader), current_data_partition_index(0) {}

// crear otro constructor??

void Task::reset(){
    data_loader->reset();
    current_data_partition_index = 0;
    for (size_t  i = 0; i < results.size(); i++)
        results[i] = 0;
}

uint16_t Task::run() {
    reset();
    while(!data_loader->endOfDataset()) {
        size_t index = split();
        apply(partitions[index]);
    }
    return combine();

}

size_t Task::split() {
    size_t reduced_index = current_data_partition_index % workers;
    data_loader->load(partitions[reduced_index], current_data_partition_index);
    current_data_partition_index++;
    return reduced_index;
}

void Task::apply(DataPartition& dp){
    if(index_from >= index_to)
        return;
    int dp_from = std::max(index_from, dp.getFirstRowIndex()) - dp.getFirstRowIndex();
    int dp_to = std::min(index_to - 1, dp.getLastRowIndex()) - dp.getFirstRowIndex() + 1;// + dp.getRowsCant()%2;
    if(dp_to > dp_from){
        size_t idx = dp.getIndex();
        const std::vector<uint16_t>& column_data = dp.getColumnData(column_to_process);
        uint16_t result = op->operate(column_data, dp_from, dp_to);
        results[idx - index_from / partition_rows] = result;
    }
}

uint16_t Task::combine() const {
    return op->operate(results);
}

void Task::setOperator(const Operator *& op) {
    this->op = op;
}

void Task::setRange(const size_t &from, const size_t &to) {
    if(to <= from)
        return;
    if ((index_to - index_from) == (to - from))
        results = std::vector<uint16_t>(to - from);
    index_from = from;
    index_to = to;
}

void Task::setColumnToProcess(const size_t &column) {
    if(column < 0 || column >= this->partition_columns)
        return;
    this->column_to_process = column;
}

void Task::setPartitionRows(const size_t& rows) {
    if(rows < 1)
        return;
    this->partition_rows = rows;
    for (size_t i = 0; i < workers; i++){
        partitions[i].setRows(rows);
    }
}






