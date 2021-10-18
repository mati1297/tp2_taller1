#include <string>
#include <iostream>
#include <sstream>
#include "task_reader.h"
#include "task.h"
#include "sum.h"
#include "max.h"
#include "min.h"

TaskReader::TaskReader(): sum(), max(), min(), mean(),
                          operators {{"sum", &sum}, {"max", &max},
                                     {"min", &min}, {"mean", &mean}} {}

/* TODO Preguntar si deberia borrar la clase. Yo no la borraria ya que tiene el map y sería
    engorroso hacerlo en un metodo de split apply combine */

Task TaskReader::read(Task & task, const uint32_t & part_columns) {
    uint32_t part_rows = 0, from = 0, to = 0, col_to_process = 0;
    std::string op;
    std::string line;

    std::getline(std::cin, line);

    std::istringstream iss(line);

    // Se valida que no haya numeros negativos
    if (line.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");

    iss >> from >> to >> part_rows >> col_to_process >> op;

    return Task(part_columns, part_rows, operators.at(op),
                from, to, col_to_process);
}



