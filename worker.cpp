#include <vector>
#include "worker.h"
#include "to_do_token.h"
#include "sum.h"

Worker::Worker(ToDoQueue *const &queue_, DataLoader *const &data_loader_,
               Result *const &result_,
               std::vector<DataPartition> *const &data_partitions_,
               const Operator *const &operator_,
               const uint32_t &col_to_process):
               queue(queue_), data_loader(data_loader_), result(result_),
               data_partitions(data_partitions_), op(operator_),
               column_to_process(col_to_process){}

void Worker::operator()() {
    run();
}

void Worker::run() const {
    while (true) {
        ToDoToken to_do_token;
        bool queue_not_empty = queue->ifNotEmptyPop(to_do_token);
        if (!queue_not_empty)
            continue;
        if (to_do_token.endOfWork())
            return;
        uint32_t part_index = to_do_token.getIndex();

        if (!data_loader->ifDatasetNotEndedLoad
                ((*data_partitions)[part_index])) {
            (*data_partitions)[part_index].setDone(true);
            continue;
        }

        Result temp_result;
        op->operate(temp_result, (*data_partitions)[part_index],
                    column_to_process);
        op->operate(*result, temp_result);

        (*data_partitions)[part_index].setDone(true);
    }
}



