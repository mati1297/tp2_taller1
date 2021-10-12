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
    size_t result_idx;
    uint32_t part_rows;
    uint32_t from;
    uint32_t to;
    uint32_t column_to_process;

public:
    /* Constructor sin parametros, se setea por defecto end en false,
     * se utiliza para crear un token de finalizacion. */

    ToDoToken();

    // Constructor en el que se cargan todos los atributos.
    ToDoToken(const bool &end_, const Operator *const &op_,
              const size_t & result_idx_, const uint32_t &part_rows_,
              const uint32_t &from, const uint32_t &to,
              const uint32_t & column_to_process_);

    // Operador asignacion.
    ToDoToken& operator=(const ToDoToken &);

    // Devuelve el flag de finalizacion.
    bool endOfWork() const;

    // Devuelve un puntero al operador.
    const Operator  *const & getOperator() const;

    // Devuelve la cantidad de filas por particion.
    const uint32_t &getPartitionRows() const;

    // Devuelve la posicion del inicio de la lectura.
    const uint32_t &getFrom() const;

    // Devuelve la posiciond del final de la lectura.
    const uint32_t &getTo() const;

    // Devuelve la columna que se debe procesar.
    const uint32_t &getColumnToProcess() const;

    // Devuelve el index donde se debe guardar el resultado.
    const size_t &getResultIndex() const;
};

#endif //TP2_TALLER1_TO_DO_TOKEN_H
