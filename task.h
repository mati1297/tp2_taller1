//
// Created by matias on 2/10/21.
//

#ifndef TP2_TALLER1_TASK_H
#define TP2_TALLER1_TASK_H


#include <cstdint>
#include <vector>
#include "data_partition.h"
#include "operator.h"
#include "file_reader.h"
#include "data_loader.h"


class Task {
    friend class TaskReader;
private:
    const Operator * op;
    const size_t workers;
    const size_t part_columns;
    size_t part_rows;
    size_t column_to_process;
    size_t index_from;
    size_t index_to;
    std::vector<Result> results;
    std::vector<DataPartition> partitions;
    DataLoader * data_loader;
    size_t current_data_partition_index;

    void setOperator(const Operator *&op);

    void setRange(const size_t& from, const size_t& to);

    void setColumnToProcess(const size_t &column);

    void setPartitionRows(const size_t& partition_rows);

    void reset();

    static size_t ceil(size_t num, size_t den);

public:
    Task(Operator * op, size_t part_columns, size_t part_rows,
         size_t column_to_process, size_t index_from,
         size_t index_to, size_t workers, DataLoader * data_loader);

    void apply(DataPartition &dp);

    Result combine() const;

    size_t split();

    Result run();
};








#endif //TP2_TALLER1_TASK_H
