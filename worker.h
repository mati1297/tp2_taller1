#ifndef TP2_TALLER1_WORKER_H
#define TP2_TALLER1_WORKER_H

#include <vector>
#include "result.h"
#include "to_do_queue.h"
#include "data_loader.h"
#include "sum.h"

class Worker {
    ToDoQueue * const queue;
    DataLoader * const data_loader;
    Result * const result;
    std::vector<DataPartition> * const data_partitions;
    const Operator * const op;
    const uint32_t column_to_process;


public:
    Worker(ToDoQueue * const & queue_, DataLoader * const & data_loader_,
           Result * const & result_,
           std::vector<DataPartition> * const & data_partitions_,
           const Operator * const & operator_, const uint32_t & col_to_process);

    void operator()();

    void run() const;
};


#endif //TP2_TALLER1_WORKER_H
