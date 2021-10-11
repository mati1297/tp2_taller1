#include "to_do_queue.h"
#include <iostream>

ToDoQueue::ToDoQueue(): m(), queue(), counter(0), new_element(0) {}

void ToDoQueue::push(const ToDoToken & new_token){
    m.lock();
    queue.push_back(new_token);
    new_element++;
    m.unlock();
}

bool ToDoQueue::ifNotEmptyPop(ToDoToken & token, int & cou) {
    m.lock();
    if(counter < new_element){
        token = queue[counter++];
        cou = counter;
        m.unlock();
        return true;
    }
    m.unlock();
    return false;
}

