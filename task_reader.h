#ifndef TP2_TALLER1_TASK_READER_H
#define TP2_TALLER1_TASK_READER_H

#include <string>
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
    const Min min;
    const Max max;
    const Mean mean;

    // Metodo privado que valida y setea el operador.
    void setupOperator(Task &task, const std::string &text) const;

    // Metodo privado que setea los rangos de lectura.
    void setupRanges(Task &task, const std::string& text_from,
                            const std::string& text_to) const;

    // Metodo privado que setea la columna que se debe procesar.
    void setupColumnToProcess(Task &task, const std::string& text) const;

    // Metodo privado que setea la cantidad de particiones por filas.
    void setupPartitionRows(Task &task, const std::string& text) const;

public:
    TaskReader();

    uint8_t read(Task& task);
};




#endif //TP2_TALLER1_TASK_READER_H
