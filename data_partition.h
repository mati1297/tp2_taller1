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

    void reset();

    void print();

    const std::vector<uint16_t> &getColumnData(const uint32_t
                                                & column_idx) const;

    void setRows(const uint32_t & rows_);

    void close();

    const uint32_t &getRows() const;
};


#endif //TP2_TALLER1_DATAPARTITION_H
