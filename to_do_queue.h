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
    std::queue<ToDoToken> queue;

public:
    ToDoQueue();

    void push(const ToDoToken & new_token);

    bool ifNotEmptyPop(ToDoToken &token);
};


#endif //TP2_TALLER1_TO_DO_QUEUE_H
