#include "to_do_queue.h"

ToDoQueue::ToDoQueue(): m(), queue(), counter(0), last_element(0) {}

void ToDoQueue::push(const ToDoToken & new_token){
    m.lock();
    queue.push_back(new_token);
    last_element++;
    m.unlock();
}

bool ToDoQueue::ifNotEmptyPop(const ToDoToken * & token) {
    m.lock();
    if(counter < last_element){
        token = &queue[counter++];
        m.unlock();
        return true;
    }
    m.unlock();
    token = nullptr;
    return false;
}
