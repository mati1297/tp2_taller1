//
// Created by matias on 4/10/21.
//

#ifndef TP2_TALLER1_DATA_LOADER_H
#define TP2_TALLER1_DATA_LOADER_H


#include "file_reader.h"
#include "data_partition.h"

class DataLoader {
    FileReader * const file_reader;
    size_t start;
    size_t end;
    size_t counter;

public:
    //DataLoader(DataLoader& original) = delete;

    explicit DataLoader(FileReader * const file_reader);

    void load(DataPartition& dp, const size_t& idx);

    bool endOfDataset();

    void setStart(const size_t& _start);

    void setEnd(const size_t& _end);
};


#endif //TP2_TALLER1_DATA_LOADER_H
