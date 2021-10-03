#ifndef TP2_TALLER1_DATAPARTITION_H
#define TP2_TALLER1_DATAPARTITION_H

#include <vector>
#include <cstdint>

class DataPartition {
private:
    enum State{
        STATE_CLEAR,
        STATE_HALF,
        STATE_FULL
    };

    size_t index;
    const size_t rows;
    const size_t columns;
    size_t _row;
    size_t _column;
    enum State state;
    std::vector<std::vector<uint16_t>> data;

public:
    DataPartition(size_t index, size_t rows, size_t columns);
    void load(const uint16_t &number);

    bool isFull() const;

    void reset(const size_t& index);

    void print();

    const std::vector<uint16_t> &getColumnData(size_t column_idx) const;

    size_t getFirstRowIndex() const;

    size_t getLastRowIndex() const;

    size_t getIndex() const;

};


#endif //TP2_TALLER1_DATAPARTITION_H
