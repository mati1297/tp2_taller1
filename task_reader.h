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
    // Constructor sin parametros.
    TaskReader();

    /* Lee de stdin, valida y carga task. Devuelve true si se pudo leer
     * y false si se alcanzo eof. */
    bool read(Task& task);
};




#endif //TP2_TALLER1_TASK_READER_H
