//
// Created by matias on 3/10/21.
//

#ifndef TP2_TALLER1_TASK_READER_H
#define TP2_TALLER1_TASK_READER_H

#include <string>
#include "task.h"
#include "min.h"
#include "sum.h"
#include "max.h"
#include "mean.h"

class Task;

class TaskReader {
private:
    const Sum sum;
    const Min min;
    const Max max;
    const Mean mean;

    void setupOperator(Task &task, const std::string &text) const;

public:

    TaskReader();

    uint8_t read(Task& task) ;

    static void setupRanges(Task &task, const std::string& text_from, const std::string& text_to) ;

    static void setupColumn(Task &task, const std::string& text) ;

    void setupPartitionRows(Task &task, const std::string& text) const;
};




#endif //TP2_TALLER1_TASK_READER_H
