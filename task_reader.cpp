#include <string>
#include <iostream>
#include "task_reader.h"
#include "task.h"
#include "sum.h"
#include "max.h"
#include "min.h"

TaskReader::TaskReader(): sum(), max(), min(), mean(),
                          operators {{"sum", &sum}, {"max", &max},
                                     {"min", &min}, {"mean", &mean}} {}

// TODO rehacer esta clase. borro directamente o hago inicializo un objeto?.

bool TaskReader::read(Task & task) {
    // Se leen los rangos.
    std::string read1, read2;
    std::cin >> read1;
    // Si se alcanzo eof se devuelve 1 indicando que termino la entrada.
    if (std::cin.eof())
        return false;
    std::cin >> read2;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupRanges(task, read1, read2);
    }
    catch(std::invalid_argument& e) {
        throw;
    }
    // Se lee la cantidad de filas por particion.
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupPartitionRows(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    // Se lee la columna a procesar.
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try{
        setupColumnToProcess(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    // Se lee la operacion.
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupOperator(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    return true;
}

void TaskReader::setupOperator(Task & task, const std::string & text) const {
    // TODO ver si catcheo esto o lo dejo asi
    task.setOperator(operators.at(text));
}

void TaskReader::setupRanges(Task & task, const std::string & text_from,
                             const std::string & text_to) const {
    uint32_t from = 0, to = 0;
    try {
        if (text_from.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        from = std::stoul(text_from);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("error al leer la fila inicial: " + msg);
    }
    try {
        if (text_to.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        to = std::stoul(text_to);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("error al leer la fila final: " + msg);
    }
    try {
        task.setRange(from, to);
    }
    catch(std::invalid_argument& e){
        throw;
    }
}

void TaskReader::setupColumnToProcess(Task & task,
                                      const std::string & text) const {
    uint32_t column = 0;
    try {
        if (text.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        column = std::stoul(text);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("error al leer la columna: " + msg);
    }
    try {
        task.setColumnToProcess(column);
    }
    catch(std::invalid_argument& e){
        throw;
    }
}

void TaskReader::setupPartitionRows(Task & task,
                                    const std::string & text) const {
    uint32_t partition_rows = 0;
    try {
        if (text.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        partition_rows = std::stoul(text);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("error al leer la cantidad "
                                    "de filas por columna: " + msg);
    }
    try {
        task.setPartitionRows(partition_rows);
    }
    catch(std::invalid_argument& e){
        throw;
    }
}


