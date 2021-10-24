#include <iostream>
#include "to_do_queue.h"

ToDoQueue::ToDoQueue(const uint8_t & max_tokens_): m(), cv_empty(),
                     cv_full(), queue(), max_tokens(max_tokens_) {}

void ToDoQueue::push(ToDoToken & new_token) {
    std::unique_lock<std::mutex> u_lock(m);
    cv_full.wait(u_lock, [&] { return queue.size() < max_tokens; });
    queue.push(std::move(new_token));
    cv_empty.notify_all();
}


ToDoToken ToDoQueue::pop(){
    std::unique_lock<std::mutex> u_lock(m);
    cv_empty.wait(u_lock, [&] { return !queue.empty(); });
    ToDoToken token = std::move(queue.front());
    queue.pop();
    cv_full.notify_all();
    return token;
}


