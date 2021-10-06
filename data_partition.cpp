#include <iostream>
#include <vector>
#include "data_partition.h"

DataPartition::DataPartition(size_t index, size_t rows,
                             size_t columns):
                             index(index), rows(rows),
                             columns(columns), _row(0),
                             _column(0), state(STATE_CLEAR),
                             data(columns,
                                  std::vector<uint16_t>(rows)) {}

void DataPartition::load(const uint16_t& number){
    if (state == STATE_FULL)
        throw std::length_error("la particion ya esta llena");

    if (state == STATE_CLEAR)
        state = STATE_HALF;

    data[_column++][_row] = number;

    if (_column == columns) {
        _column = 0;
        _row++;
    }
    if (_row == rows) {
        close();
    }
}

void DataPartition::reset(const size_t& index){
    this->index = index;
    _column = _row = 0;
    state = STATE_CLEAR;
}

bool DataPartition::isFull() const{
    if (state == STATE_FULL)
        return true;
    return false;
}

/*void DataPartition::print(){
    std::cout << "Particion:" << std::endl;
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < columns; j++)
            std::cout << data[j][i] << " ";
        std::cout << std::endl;
    }
}*/

const std::vector<uint16_t>&
        DataPartition::getColumnData(size_t column_idx) const{
    if (column_idx >= columns)
        throw std::invalid_argument("esa columna no existe en la particion");
    return data[column_idx];
}

size_t DataPartition::getFirstRowIndex() const{
    return index * rows;
}

size_t DataPartition::getLastRowIndex() const {
    return (index + 1) * rows - 1;
}

size_t DataPartition::getIndex() const {
    return index;
}

void DataPartition::setRows(const size_t& _rows) {
    if (this->rows == _rows)
        return;
    this->rows = _rows;
    for (size_t i = 0; i < columns; i++)
        data[i] = std::vector<uint16_t>(_rows);
}

void DataPartition::close() {
    if (_column < columns and _column > 0) {
        while (_column < columns and _column > 0)
            data[_column++][_row] = 0;
        _column = 0;
        _row++;
    }
    state = STATE_FULL;
}


