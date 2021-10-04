//
// Created by matias on 2/10/21.
//

#include <vector>
#include <algorithm>
#include "task.h"
#include "data_partition.h"
#include "operator.h"

Task::Task(Operator * op, size_t part_columns, size_t part_rows,
           size_t column_to_process, size_t index_from, size_t index_to,
           size_t workers, DataLoader * data_loader):
        op(op), workers(workers), part_columns(part_columns),
        part_rows(part_rows), column_to_process(column_to_process),
        index_from(index_from), index_to(index_to),
        results(ceil(index_to - index_from, part_rows)),
        partitions(workers, DataPartition(0, part_rows, part_columns)),
        data_loader(data_loader), current_data_partition_index(0) {}

// crear otro constructor??

void Task::reset(){
    data_loader->reset();
    current_data_partition_index = 0;
    for (size_t  i = 0; i < results.size(); i++)
        results[i] = 0;
}

Result Task::run() {
    reset();
    while (!data_loader->endOfDataset()) {
        size_t index = split();
        apply(partitions[index]);
    }
    Result result = combine();
    op->printResult(result);
    return result;
}

size_t Task::split() {
    size_t reduced_index = current_data_partition_index % workers;
    data_loader->load(partitions[reduced_index], current_data_partition_index);
    current_data_partition_index++;
    return reduced_index;
}

void Task::apply(DataPartition& dp){
    if (index_from >= index_to)
        return;
    int dp_from = std::max(index_from,
                           dp.getFirstRowIndex()) - dp.getFirstRowIndex();
    int dp_to = std::min(index_to - 1,
                         dp.getLastRowIndex()) - dp.getFirstRowIndex() + 1;
    if (dp_to > dp_from){
        size_t idx = dp.getIndex();
        const std::vector<uint16_t>& column_data =
                dp.getColumnData(column_to_process);
        op->operate(results[idx - index_from / part_rows],
                    column_data, dp_from, dp_to);
    }
}

Result Task::combine() const {
    Result result;
    op->operate(result, results);
    return result;
}

void Task::setOperator(const Operator *& op) {
    this->op = op;
}

void Task::setRange(const size_t &from, const size_t &to) {
    if (to <= from)
        return;
    if ((index_to - index_from) != (to - from))
        results = std::vector<Result>(
                ceil(to - from, part_rows));
    index_from = from;
    index_to = to;
}

void Task::setColumnToProcess(const size_t &column) {
    if (column < 0 || column >= this->part_columns)
        return;
    this->column_to_process = column;
}

void Task::setPartitionRows(const size_t& rows) {
    if (rows < 1)
        return;
    if (this->part_rows == rows)
        return;
    this->part_rows = rows;
    for (size_t i = 0; i < workers; i++){
        partitions[i].setRows(rows);
    }
    results = std::vector<Result>(
            ceil(index_to - index_from, part_rows));
}

size_t Task::ceil(size_t num, size_t den) {
    return num / den + ((num%den) != 0);
}







