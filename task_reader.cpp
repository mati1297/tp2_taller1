//
// Created by matias on 3/10/21.
//

#include <string>
#include <iostream>
#include "task_reader.h"
#include "task.h"
#include "sum.h"
#include "max.h"
#include "min.h"

TaskReader::TaskReader(): sum(), min(), max(), mean() {}

uint8_t TaskReader::read(Task &task) {
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
        throw e;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupPartitionRows(task, read1);
    }
    catch(std::invalid_argument& e){
        throw e;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try{
        setupColumn(task, read1);
    }
    catch(std::invalid_argument& e){
        throw e;
    }
    std::cin >> read1;
    if (std::cin.eof())
        throw std::invalid_argument("faltan parametros de la tarea");
    try {
        setupOperator(task, read1);
    }
    catch(std::invalid_argument& e){
        throw e;
    }
    return 0;
}

void TaskReader::setupOperator(Task &task, const std::string& text) const {
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

void TaskReader::setupRanges(Task &task, const std::string& text_from,
                             const std::string& text_to) {
    size_t from, to;
    try {
        if(text_from.find('-') != std::string::npos)
            throw std::invalid_argument("");
        from = std::stoull(text_from);
    }
    catch(std::exception& e){
        throw std::invalid_argument("error al leer la fila inicial");
    }
    try {
        if(text_to.find('-') != std::string::npos)
            throw std::invalid_argument("");
        to = std::stoull(text_to);
    }
    catch(std::exception& e){
        throw std::invalid_argument("error al leer la fila final");
    }
    try {
        task.setRange(from, to);
    }
    catch (std::invalid_argument& e){
        throw e;
    }
}

void TaskReader::setupColumn(Task &task, const std::string& text) {
    size_t column;
    try {
        if(text.find('-') != std::string::npos)
            throw std::invalid_argument("");
        column = std::stoull(text);
    }
    catch(std::exception& e){
        throw std::invalid_argument("error al leer la columna");
    }
    try {
        task.setColumnToProcess(column);
    }
    catch (std::invalid_argument& e){
        throw e;
    }
}

void TaskReader::setupPartitionRows(Task &task, const std::string& text) {
    size_t partition_rows;
    try {
        if(text.find('-') != std::string::npos)
            throw std::invalid_argument("");
        partition_rows = std::stoull(text);
    }
    catch(std::exception& e){
        throw std::invalid_argument("error al leer la cantidad de"
                                    " filas por particion");
    }
    try {
        task.setPartitionRows(partition_rows);
    }
    catch (std::invalid_argument& e){
        throw e;
    }
}


