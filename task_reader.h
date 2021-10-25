#ifndef TP2_TALLER1_TASK_READER_H
#define TP2_TALLER1_TASK_READER_H

#include <string>
#include <map>
#include "task.h"
#include "min.h"
#include "sum.h"
#include "max.h"
#include "mean.h"

class Task;

/* Clase que se encarga de leer datos de stdin y cargarlos
 * en una task. Contiene como atributos instancias de operaciones
 * que utilizara para cargarlas en las tareas. */
class TaskReader {
private:
    const Sum sum;
    const Max max;
    const Min min;
    const Mean mean;
    const std::map<const std::string, const Operator*> operators;

public:
    // Constructor sin parametros.
    TaskReader();

    /* Lee de stdin, valida y carga task. Recibe como parametro
     * la task y la cantidad de columnas por particion. */
    Task read(Task &task, const uint32_t &part_columns);
};




#endif //TP2_TALLER1_TASK_READER_H
