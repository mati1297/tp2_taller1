#ifndef TP2_TALLER1_TASK_H
#define TP2_TALLER1_TASK_H


#include <cstdint>
#include <vector>
#include "data_partition.h"
#include "operator.h"
#include "file_reader.h"
#include "data_loader.h"
#include "to_do_queue.h"

/* Clase que representa una tarea a realizar, se encarga de cargar
 * en la queue de tareas las tareas que corresponden a si misma.
 * Posee como atributos un puntero al operador que utiliza, la cantidad
 * de filas y columnas por particion, que columna debe procesar, y desde
 * y hasta que fila se debe leer. */
class Task {
private:
    const Operator * op;
    const uint32_t part_columns;
    uint32_t part_rows;
    uint32_t column_to_process;
    uint32_t index_from;
    uint32_t index_to;

    /* Funcion auxiliar estatica utilizada por la clase que permite
     * calcular el techo de una division. */
    static uint32_t ceil(const uint32_t & num, const uint32_t & den);

public:
    /* Constructor, toma como parametros la cantidad de columnas y filas por
     * particion, el operador, desde y hasta que fila se debe procesar
     * y la columna que se debe procesar.*/
    Task(const uint32_t & part_columns_, const uint32_t & part_rows_,
         const Operator *op_, const uint32_t &from, const uint32_t &to,
         const uint32_t & col_to_proc);


    /* Metodo que carga la cola con las tareas correspondientes a esta
     * tarea. */
    void loadQueue(ToDoQueue & queue, const size_t & result_idx);
};

#endif //TP2_TALLER1_TASK_H
