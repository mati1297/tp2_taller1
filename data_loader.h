#ifndef TP2_TALLER1_DATA_LOADER_H
#define TP2_TALLER1_DATA_LOADER_H


#include "file_reader.h"
#include "data_partition.h"

class DataLoader {
    FileReader * const file_reader;
    uint32_t start;
    uint32_t end;
    uint32_t counter;

public:
    explicit DataLoader(FileReader * const & file_reader);

    void load(DataPartition & dp);

    bool endOfDataset() const;

    void setStart(const uint32_t & start_);

    void setEnd(const uint32_t & end_);
};

#endif //TP2_TALLER1_DATA_LOADER_H
