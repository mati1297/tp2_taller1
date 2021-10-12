#ifndef TP2_TALLER1_TO_DO_TOKEN_H
#define TP2_TALLER1_TO_DO_TOKEN_H


#include "data_partition.h"

/* Representa una orden de procesamiento o de finalizacion,
 * posee un index correspondiente a una de las particiones
 * de datos existente en memoria y un flag de trabajo terminado.
 */
class ToDoToken {
    uint32_t idx;
    bool end;

public:
    // Constructor por sin parametros.
    ToDoToken();

    /* Constructor. Se le pasa el index y el flag
     * de finalizacion. */
    ToDoToken(const uint32_t & idx_, const bool & end_);

    // Operador asignacion.
    ToDoToken& operator=(const ToDoToken &);

    // Devuelve el index contenido en el token.
    const uint32_t & getIndex() const;

    // Devuelve el flag de finalizacion.
    bool endOfWork() const;
};


#endif //TP2_TALLER1_TO_DO_TOKEN_H
