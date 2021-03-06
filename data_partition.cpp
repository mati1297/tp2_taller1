#include <iostream>
#include <vector>
#include <utility>
#include "data_partition.h"

DataPartition::DataPartition(const uint32_t & rows,
                             const uint32_t & columns): rows(rows),
                             columns(columns), _row(0),
                             _column(0), closed(false),
                             data(columns,
                             std::vector<uint16_t>(rows)) {
}

DataPartition::DataPartition(DataPartition &&orig) noexcept:
                             rows(orig.rows), columns(orig.columns),
                             _row(orig._row), _column(orig._column),
                             closed(orig.closed), data(std::move(orig.data)) {
    orig.rows = orig.columns = orig._row = orig._column = 0;
    orig.closed = false;
}

DataPartition &DataPartition::operator=(DataPartition &&orig) noexcept {
    rows = orig.rows;
    columns = orig.columns;
    _row = orig._row;
    _column = orig._column;
    closed = orig.closed;
    data = std::vector<std::vector<uint16_t>>(0);
    orig.rows = orig.columns = orig._row = orig._column = 0;
    orig.closed = false;
    return *this;
}

void DataPartition::load(const uint16_t & number) {
    // Si la particion esta cerrada, se devuelve una excepcion.
    if (closed)
        throw std::length_error("la particion ya esta llena");

    // Se guarda en la posicion que toca.
    data[_column++][_row] = number;

    // Si se alcanzo el fin de la fila se pasa a la siguiente.
    if (_column == columns) {
        _column = 0;
        _row++;
    }
    // Si se lleno completamente, se cierra.
    if (_row == rows) {
        close();
    }
}

void DataPartition::reset() {
    // Si se habia achicado anteriormente, se cambia el tamanio al original.
    if (_row < rows && _row != 0) {
        for (uint32_t i = 0; i < columns; i++){
            data[i].resize(rows);
        }
    }
    // Se setean los contadores a 0 y se marca como no cerrada.
    _column = _row = 0;
    closed = false;
}

bool DataPartition::isClosed() const {
    return closed;
}

const std::vector<uint16_t>&
        DataPartition::getColumnData(const uint32_t & column_idx) const {
    if (column_idx >= columns)
        throw std::invalid_argument("esa columna no existe en la particion");
    return data[column_idx];
}

void DataPartition::close() {
    // Si ya esta cerrado no se hace nada.
    if (closed)
        return;
    /* Se chequea si falta terminar una fila, si es asi
     * se rellena con 0. */
    if (_column < columns && _column > 0) {
        while (_column < columns && _column > 0)
            data[_column++][_row] = 0;
        _column = 0;
        _row++;
    }
    /* Si no se completaron todas las filas, se achica el vector
     * que las contiene (esto se va a realizar solo una vez,
     * en la ultima particion que se lee). */
    if (_row < rows && _row != 0) {
        for (uint32_t i = 0; i < columns; i++) {
            data[i].resize(_row);
        }
    }
    // Se cierra.
    closed = true;
}

const uint32_t & DataPartition::getFullRows() const {
    return _row;
}







