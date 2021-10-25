#ifndef TP2_TALLER1_TO_DO_QUEUE_H
#define TP2_TALLER1_TO_DO_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "to_do_token.h"

/* Cola bloqueante y bounded proteigda donde se guardan
 * los tokens con las ordenes de procedimiento para
 * que sean leidas por los Workers. Es protegida
 * ya que es un recurso compartido
 * por el hilo principal y los Workers. La cola bloquea
 * si se quiere popear estando vacia y si se quiere pushear
 * estando llena (segun max_tokens). */
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

    /* Coloca un token (el cual se mueve) al final de la
     * cola. */
    void push(ToDoToken & new_token);

    // Devuelve el primer token de la cola por movimiento y lo quita.
    ToDoToken pop();
};


#endif //TP2_TALLER1_TO_DO_QUEUE_H
