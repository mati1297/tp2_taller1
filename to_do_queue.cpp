#include "to_do_queue.h"

ToDoQueue::ToDoQueue(): m(), queue() {}

void ToDoQueue::push(const ToDoToken & new_token) {
    m.lock();
    queue.push(new_token);
    m.unlock();
}

bool ToDoQueue::ifNotEmptyPop(ToDoToken & token) {
    m.lock();
    if (!queue.empty()) {
        token = queue.front();
        queue.pop();
        m.unlock();
        return true;
    }
    m.unlock();
    return false;
}


