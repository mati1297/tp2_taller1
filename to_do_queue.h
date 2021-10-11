#ifndef TP2_TALLER1_TO_DO_QUEUE_H
#define TP2_TALLER1_TO_DO_QUEUE_H

#include <queue>
#include <mutex>
#include "to_do_token.h"

/* Cola protegida donde se guardan los tokens con las
 * ordenes de procedimiento para que sean leidas por
 * los Workers. Es protegida ya que es un recurso compartido
 * por el hilo principal y los Workers. */
class ToDoQueue {
    std::mutex m;
    std::queue<ToDoToken> queue;

public:
    // Constructor por defecto.
    ToDoQueue();

    /* Coloca un token (el cual se copia) al final de la
     * cola. */
    void push(const ToDoToken & new_token);

    /* Si la cola no esta vacia se quita el primer
     * elemento, se copia en el token pasado como
     * parametro y se devuelve true. En caso
     * contrario se devuelve false. */
    bool ifNotEmptyPop(ToDoToken & token);
};


#endif //TP2_TALLER1_TO_DO_QUEUE_H
