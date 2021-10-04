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
        //exception
        return 1;
    setupRanges(task, read1, read2);
    std::cin >> read1;
    if (std::cin.eof())
        return 1;
    setupPartitionRows(task, read1);
    std::cin >> read1;
    if (std::cin.eof())
        return 1;
    setupColumn(task, read1);
    std::cin >> read1;
    if (std::cin.eof())
        return 1;
    try {
        setupOperator(task, read1);
    }
    catch(std::exception& e){
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

void TaskReader::setupPartitionRows(Task &task, const std::string& text) {
    size_t partition_rows = std::stoull(text);
    //validar
    task.setPartitionRows(partition_rows);
}


