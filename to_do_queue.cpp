#include "to_do_queue.h"

ToDoQueue::ToDoQueue(): m(), queue() {}

void ToDoQueue::push(const ToDoToken & new_token) {
    // Se utiliza lock guard, que utiliza RAII.
    std::lock_guard<std::mutex> lock_guard(m);
    queue.push(new_token);
}

bool ToDoQueue::ifNotEmptyPop(ToDoToken & token) {
    // Se utiliza lock guard, que funciona con RAII.
    std::lock_guard<std::mutex> lock_guard(m);
    if (!queue.empty()) {
        token = queue.front();
        queue.pop();
        return true;
    }
    return false;
}


