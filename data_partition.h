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

    uint32_t index;
    uint32_t rows;
    const uint32_t columns;
    uint32_t _row;
    uint32_t _column;
    enum State state;
    std::vector<std::vector<uint16_t>> data;

public:
    DataPartition(const uint32_t & index, const uint32_t & rows,
                  const uint32_t & columns);

    void load(const uint16_t &number);

    bool isFull() const;

    void reset(const uint32_t & index_);

    void print();

    const std::vector<uint16_t> &getColumnData(const uint32_t
                                                & column_idx) const;

    uint32_t getFirstRowIndex() const;

    uint32_t getLastRowIndex() const;

    uint32_t getIndex() const;

    void setRows(const uint32_t & rows_);

    void close();
};


#endif //TP2_TALLER1_DATAPARTITION_H
