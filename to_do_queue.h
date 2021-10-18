#ifndef TP2_TALLER1_TO_DO_QUEUE_H
#define TP2_TALLER1_TO_DO_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "to_do_token.h"

/* Cola protegida donde se guardan los tokens con las
 * ordenes de procedimiento para que sean leidas por
 * los Workers. Es protegida ya que es un recurso compartido
 * por el hilo principal y los Workers. */
class ToDoQueue {
    std::mutex m;
    std::condition_variable cv_empty, cv_full;
    std::queue<ToDoToken> queue;
    uint8_t max_tokens;

public:
    // Constructor sin parametros.
    explicit ToDoQueue(const uint8_t & max_tokens_);

    // No tiene constructor por copia.
    ToDoQueue(const ToDoQueue & orig) = delete;

    // No tiene constructor por movimiento.
    ToDoQueue(const ToDoQueue && orig) = delete;

    // No tiene operador =.
    ToDoQueue & operator=(const ToDoQueue & orig) = delete;

    /* Coloca un token (el cual se copia) al final de la
     * cola. */
    void push(const ToDoToken & new_token);

    ToDoToken pop();
};


#endif //TP2_TALLER1_TO_DO_QUEUE_H
