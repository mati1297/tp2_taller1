#include <utility>
#include "to_do_queue.h"

ToDoQueue::ToDoQueue(const uint8_t & max_tokens_): m(), cv_empty(),
                     cv_full(), queue(), max_tokens(max_tokens_) {}

void ToDoQueue::push(ToDoToken & new_token) {
    std::unique_lock<std::mutex> u_lock(m);
    /* Se hace la cola bounded. Si se tiene la maxima cantidad
     * de tokens permitida, se espera hasta que se notifique al
     * condition variable que se quito un elemento. */
    cv_full.wait(u_lock, [&] { return queue.size() < max_tokens; });
    queue.push(std::move(new_token));
    /* Una vez que se agrego un elemento, se notifica al condition
     * variable que la cola ya no esta vacia. */
    cv_empty.notify_all();
}


ToDoToken ToDoQueue::pop(){
    std::unique_lock<std::mutex> u_lock(m);
    // Si la cola esta vacia se espera.
    cv_empty.wait(u_lock, [&] { return !queue.empty(); });
    ToDoToken token = std::move(queue.front());
    queue.pop();
    cv_full.notify_all();
    return token;
}


