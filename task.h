#ifndef TP2_TALLER1_TASK_H
#define TP2_TALLER1_TASK_H


#include <cstdint>
#include <vector>
#include "data_partition.h"
#include "operator.h"
#include "file_reader.h"
#include "data_loader.h"

/* Clase que representa una tarea a realizar, es la encargada
 * de inicializar los hilos y enviarles sus tareas.
 * Posee como atributos un puntero al operador que debe utilizar,
 * la cantidad de workers_cant que posee, la cantidad de particiones por
 * columnas y filas, que columna debe procesar, desde y hasta que indices
 * de filas debe procesar y un puntero al data loader. */
class Task {
private:
    const Operator * op;
    const uint8_t workers_cant;
    const uint32_t part_columns;
    uint32_t part_rows;
    uint32_t column_to_process;
    uint32_t index_from;
    uint32_t index_to;
    DataLoader *data_loader;

    // Resetea el data loader.
    void resetDataLoader();

    /* Funcion auxiliar estatica utilizada por la clase que permite
     * calcular el techo de una division. */
    static uint32_t ceil(const uint32_t & num, const uint32_t & den);

public:
    /* Constructor, toma como parametros las columnas por particion,
     * la cantidad de workers_cant y un puntero al data loader.
     * Pre:
     *      data_loader debe apuntar a un objeto tipo DataLoader
     *          valido. */
    Task(const uint32_t & part_columns, const uint8_t & workers,
          DataLoader * const & data_loader);

    /* Metodo que ejecuta la tarea. Este inicializa las particiones y workers_cant,
     * y les asigna sus tareas. */
    Result run();

    /* Setea el operador que ejecutara la tarea.
     * Pre:
     *      op debe apuntar a un objeto Operador valido. */
    void setOperator(const Operator * const & op);

    // Setea el rango de filas en el que operara la tarea.
    void setRange(const uint32_t & from, const uint32_t & to);

    // Setea la columna sobre la que operara la tarea.
    void setColumnToProcess(const uint32_t & column);

    // Setea la cantidad de filas que tendra cada particion.
    void setPartitionRows(const uint32_t & partition_rows);
};

#endif //TP2_TALLER1_TASK_H
