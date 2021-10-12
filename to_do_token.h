#ifndef TP2_TALLER1_TO_DO_TOKEN_H
#define TP2_TALLER1_TO_DO_TOKEN_H


#include "data_partition.h"
#include "operator.h"

/* Representa una orden de procesamiento o de finalizacion,
 * posee un index correspondiente a una de las particiones
 * de datos existente en memoria y un flag de trabajo terminado.
 */
class ToDoToken {
    bool end;
    const Operator * op;
    size_t result_idx;
    uint32_t part_rows;
    uint32_t from;
    uint32_t to;
    uint32_t column_to_process;

public:
    // Constructor por sin parametros.
    ToDoToken();

    ToDoToken(const bool &end_, const Operator *const &op_,
              const size_t & result_idx_, const uint32_t &part_rows_,
              const uint32_t &from, const uint32_t &to,
              const uint32_t & column_to_process_);

    explicit ToDoToken(const bool &end_);

    // Operador asignacion.
    ToDoToken& operator=(const ToDoToken &);

    // Devuelve el flag de finalizacion.
    bool endOfWork() const;

    const Operator  *const &getOperator() const;

    const uint32_t &getPartitionRows() const;

    const uint32_t &getFrom() const;

    const uint32_t &getTo() const;

    const uint32_t &getColumnToProcess() const;

    const size_t &getResultIndex() const;
};


#endif //TP2_TALLER1_TO_DO_TOKEN_H
