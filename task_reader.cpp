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

TaskReader::TaskReader(): sum(), min(), max() {}

void TaskReader::read(Task &task) {
    std::string read1, read2;
    std::cin >> read1;
    std::cin >> read2;
    setupRanges(task, read1, read2);
    std::cin >> read1;
    setupColumn(task, read1);
    std::cin >> read1;
    setupPartitionRows(task, read1);
    std::cin >> read1;
    setupOperator(task, read1);
}

void TaskReader::setupOperator(Task &task, const std::string& text) const{
    const Operator * op = nullptr;
    if(text == "sum")
        op = &sum;
    else if(text == "min")
        op = &min;
    else if(text == "max")
        op = &max;
    else{
        throw std::invalid_argument("operador incorrecto");
    }
    task.setOperator(op);
}

void TaskReader::setupRanges(Task &task, const std::string& text_from, const std::string& text_to) {
    //chequeos de conversion
    size_t from = std::stoull(text_from);
    size_t to = std::stoull(text_to);
    task.setRange(from, to);
}

void TaskReader::setupColumn(Task &task, const std::string& text) {
    //chequeos de conversion
    size_t column = std::stoull(text);
    task.setColumnToProcess(column);
}

void TaskReader::setupPartitionRows(Task &task, const std::string& text) const {
    size_t partition_rows = std::stoull(text);
    //validar
    task.setPartitionRows(partition_rows);
}


