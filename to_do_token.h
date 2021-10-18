#ifndef TP2_TALLER1_TO_DO_TOKEN_H
#define TP2_TALLER1_TO_DO_TOKEN_H


#include "data_partition.h"
#include "operator.h"

/* Representa una orden de procesamiento o de finalizacion,
 * posee como atributos, cual es el operador a utilizar,
 * el index donde se debe guardar el resultado, cantidad
 * de filas, desde y hasta donde se debe leer y que
 * columna se debe procesar. */
class ToDoToken {
    bool end;
    const Operator * op;
    const DataPartition dp;
    size_t result_idx;
    uint32_t column_to_process;

public:
    /* Constructor sin parametros, se setea por defecto end en false,
     * se utiliza para crear un token de finalizacion. */
    ToDoToken();

    // Constructor en el que se cargan todos los atributos.
    ToDoToken(const bool &end_, const Operator * op_,
              const DataPartition & dp, const size_t & result_idx_,
              const uint32_t & column_to_process_);

    // Operador asignacion.
    ToDoToken& operator=(const ToDoToken &);

    // Devuelve el flag de finalizacion.
    bool endOfWork() const;

    // Devuelve un puntero al operador.
    const Operator  *const & getOperator() const;

    // Devuelve la columna que se debe procesar.
    const uint32_t &getColumnToProcess() const;

    // Devuelve el index donde se debe guardar el resultado.
    const size_t &getResultIndex() const;

    const DataPartition & getDataPartition() const;
};

#endif //TP2_TALLER1_TO_DO_TOKEN_H
