#include <iostream>
#include <vector>
#include "data_partition.h"

DataPartition::DataPartition(const uint32_t & index, const uint32_t & rows,
                             const uint32_t & columns): rows(rows),
                             columns(columns), _row(0),
                             _column(0), state(STATE_CLEAR),
                             data(columns,
                                  std::vector<uint16_t>(rows)), done(true), m() {}

DataPartition::DataPartition(const DataPartition &orig): rows(orig.rows), columns(orig.columns),
_row(orig._row), _column(orig._column), state(orig.state), data(orig.data), done(orig.done), m() {}

void DataPartition::load(const uint16_t & number) {
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

void DataPartition::reset() {
    if (_row < rows && _row != 0) {
        for(uint32_t i = 0; i < columns; i++){
            data[i].resize(rows);
        }
    }
    _column = _row = 0;
    state = STATE_CLEAR;

}

bool DataPartition::isFull() const {
    if (state == STATE_FULL)
        return true;
    return false;
}

const std::vector<uint16_t>&
        DataPartition::getColumnData(const uint32_t & column_idx) const {
    if (column_idx >= columns)
        throw std::invalid_argument("esa columna no existe en la particion");
    return data[column_idx];
}

void DataPartition::setRows(const uint32_t & rows_) {
    if (this->rows == rows_)
        return;
    this->rows = rows_;
    for (uint32_t i = 0; i < columns; i++)
        data[i] = std::vector<uint16_t>(rows_);
}

void DataPartition::close() {
    if (_column < columns && _column > 0) {
        while (_column < columns && _column > 0)
            data[_column++][_row] = 0;
        _column = 0;
        _row++;
    }
    //esto estoy seguro que solo pasa una vez.
    if (_row < rows && _row != 0) {
        for (uint32_t i = 0; i < columns; i++) {
            data[i].resize(_row);
        }
    }
    state = STATE_FULL;
}

const uint32_t & DataPartition::getRows() const {
    return _row;
}

void DataPartition::setDone(bool done_) {
    m.lock();
    done = done_;
    m.unlock();
}

bool DataPartition::isDone() const {
    return done;
}




