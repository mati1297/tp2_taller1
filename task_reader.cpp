#include <string>
#include <iostream>
#include "task_reader.h"
#include "task.h"
#include "sum.h"
#include "max.h"
#include "min.h"
#include "string_to_num.h"

TaskReader::TaskReader(): sum(), min(), max(), mean() {}

uint8_t TaskReader::read(Task & task) {
    std::string read1, read2;
    std::cin >> read1;
    if (std::cin.eof())
        return 1;
    std::cin >> read2;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupRanges(task, read1, read2);
    }
    catch(std::invalid_argument& e) {
        throw;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupPartitionRows(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try{
        setupColumnToProcess(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupOperator(task, read1);
    }
    catch(std::invalid_argument& e){
        throw;
    }
    return 0;
}

void TaskReader::setupOperator(Task & task, const std::string & text) const {
    const Operator * op = nullptr;
    if (text == "sum")
        op = &sum;
    else if (text == "min")
        op = &min;
    else if (text == "max")
        op = &max;
    else if (text == "mean")
        op = &mean;
    else
        throw std::invalid_argument("operador incorrecto");
    task.setOperator(op);
}

void TaskReader::setupRanges(Task & task, const std::string & text_from,
                             const std::string & text_to) const {
    uint32_t from = 0, to = 0;
    try {
        from = StringToNum::stou32(text_from);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("error al leer la fila inicial: " + msg);
    }
    try {
        to = StringToNum::stou32(text_to);
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
        column = StringToNum::stou32(text);
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
        partition_rows = StringToNum::stou32(text);
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


