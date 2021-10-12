#include <cstdint>
#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>
#include "task.h"
#include "data_partition.h"
#include "operator.h"
#include "to_do_queue.h"
#include "worker.h"

Task::Task(const uint32_t & part_columns, const uint8_t & workers,
           DataLoader * const & data_loader):
        op(nullptr), workers_cant(workers), part_columns(part_columns),
        part_rows(1), column_to_process(0),
        index_from(0), index_to(1),
        data_loader(data_loader) {}

void Task::resetDataLoader(){
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
}

Result Task::run() {
    // Se resetea el data loader.
    resetDataLoader();
    ToDoQueue queue;
    std::vector<DataPartition>
            partitions(workers_cant, DataPartition(part_rows, part_columns));
    Result result;

    // Si no se configuro el operador, se lanza excepcion.
    if (op == nullptr)
        throw std::invalid_argument("no hay un operador designado");


    // Se carga el vector de workers_cant utilizando su constructor por copia.
    std::vector<Worker> workers_vector(workers_cant,
                                       Worker(&queue, data_loader,
                                              &result, &partitions,
                                              op, column_to_process));

    // Se crea el vector de workers_cant.
    std::vector<std::thread> threads_vector(workers_cant);

    // Se lanzan los threads, uno por worker.
    for (uint8_t i = 0; i < workers_cant; i++)
        threads_vector[i] = std::thread(workers_vector[i]);

    /* Se setean todas las particiones con su flag done en true para entrar
     * de manera correcta al siguiente ciclo. */
    for(uint8_t i = 0; i < workers_cant; i++)
        partitions[i].setDone(true);

    /* Mientras que no se alcance el fin del dataset y no se lean todas
     * las particiones, se van cargando (y recargando) y procesando
     * las distintas particiones. */
    for (uint32_t j = 0; j < ceil(index_to - index_from, part_rows) &&
                            !data_loader->endOfDataset(); ){
        /* Se recorren todas las particiones para ver en cuales el trabajo
         * esta terminado, cuando se encuentra una, se asigna ese indice a
         * un token y se agrega a la cola de to do, luego se suma 1 al
         * contador. */
        for (uint32_t i = 0; i < workers_cant; i++){
            if (partitions[i].isDone()) {
                partitions[i].setDone(false);
                queue.push(ToDoToken(i, false));
                j++;
            }
            if (j >= ceil(index_to - index_from, part_rows))
                break;
        }
    }

    /* Una vez terminado, se agrega un token por worker que indica
     * el fin del trabajo. */
    for (uint8_t i = 0; i < workers_cant; i++){
        queue.push(ToDoToken(0, true));
    }
    // Luego se joinean todos los threads.
    for (uint8_t i = 0; i < workers_cant; i++)
        threads_vector[i].join();

    // Se devuelve el resultado.
    return result;
}


void Task::setOperator(const Operator * const & op) {
    this->op = op;
}

void Task::setRange(const uint32_t & from, const uint32_t & to) {
    if (to <= from)
        throw std::invalid_argument("la fila inicial es mayor que la final");
    index_from = from;
    index_to = to;
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
}

void Task::setColumnToProcess(const uint32_t & column) {
    if (column >= this->part_columns)
        throw std::invalid_argument("la columna ingresada no es valida");
    this->column_to_process = column;
}

void Task::setPartitionRows(const uint32_t & rows) {
    if (rows < 1)
        throw std::invalid_argument("la cantidad de columnas no puede ser 0");
    if (this->part_rows == rows)
        return;
    this->part_rows = rows;
    data_loader->setStart(index_from * part_columns);
    data_loader->setEnd(index_to * part_columns);
}

uint32_t Task::ceil(const uint32_t & num, const uint32_t & den) {
    return num / den + ((num%den) != 0);
}







