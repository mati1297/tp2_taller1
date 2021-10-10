//
// Created by matias on 7/10/21.
//

#include <iostream>
#include "worker.h"
#include "to_do_token.h"

Worker::Worker(ToDoQueue *const &queue_, DataLoader *const &data_loader_, Result *const &result_,
               std::vector<DataPartition> *const &data_partitions_, const Operator *const &operator_,
               const uint32_t &col_to_process):
        queue(queue_), data_loader(data_loader_), result(result_),
        data_partitions(data_partitions_), op(operator_), column_to_process(col_to_process),
        index(0) {}

void Worker::operator()() {
    const ToDoToken * to_do_token;
    while(true){
        bool not_empty = queue->ifNotEmptyPop(to_do_token);
        if(!not_empty) {
            std::cout << "Continue" << std::endl;
            continue;
        }
        if(to_do_token->endOfWork()) {
            std::cout << "return" << std::endl;
            return;
        }
        index = to_do_token->getIndex();
        if(!data_loader->endOfDataset())
            data_loader->load((*data_partitions)[index]);
        else
            return;
        try {
            Result temp_result;
            op->operate(temp_result, (*data_partitions)[to_do_token->getIndex()], column_to_process);
            op->operate(*result, temp_result);
        }
        catch(std::invalid_argument& e) {
            throw;
        }
        (*data_partitions)[index].setDone(true);
    }
}

uint32_t Worker::getIndex() const {
    return index;
}


