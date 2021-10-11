//
// Created by matias on 6/10/21.
//

#ifndef TP2_TALLER1_TO_DO_QUEUE_H
#define TP2_TALLER1_TO_DO_QUEUE_H

#include <queue>
#include <mutex>
#include "to_do_token.h"

class ToDoQueue {
    std::mutex m;
    std::vector<ToDoToken> queue;
    uint32_t counter;
    uint32_t new_element;

public:
    ToDoQueue();

    void push(const ToDoToken & new_token);

    bool ifNotEmptyPop(ToDoToken &token, int &);
};


#endif //TP2_TALLER1_TO_DO_QUEUE_H
