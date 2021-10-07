#ifndef TP2_TALLER1_TASK_H
#define TP2_TALLER1_TASK_H


#include <cstdint>
#include <vector>
#include "data_partition.h"
#include "operator.h"
#include "file_reader.h"
#include "data_loader.h"


class Task {
private:
    const Operator * op;
    const uint32_t workers;
    const uint32_t part_columns;
    uint32_t part_rows;
    uint32_t column_to_process;
    uint32_t index_from;
    uint32_t index_to;
    Result result;
    std::vector<DataPartition> partitions;
    DataLoader * data_loader;

    void reset();

    static uint32_t ceil(const uint32_t & num, const uint32_t & den);

public:
    Task(const uint32_t & part_columns, const uint32_t & workers,
          DataLoader *const & data_loader);

    void apply(const DataPartition &dp);

    //Result combine() const;

    void split();

    Result run();

    void setOperator(const Operator * const & op);

    void setRange(const uint32_t & from, const uint32_t & to);

    void setColumnToProcess(const uint32_t & column);

    void setPartitionRows(const uint32_t & partition_rows);
};








#endif //TP2_TALLER1_TASK_H
