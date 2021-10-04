//
// Created by matias on 4/10/21.
//

#include "data_loader.h"
#include "file_reader.h"

DataLoader::DataLoader(FileReader * const file_reader):
                       file_reader(file_reader) {}

void DataLoader::reset(){
    file_reader->reset();
}

bool DataLoader::endOfDataset(){
    return file_reader->eof();
}

void DataLoader::load(DataPartition &dp, const size_t& idx) const {
    uint16_t number;
    if (!file_reader->peekEof()){
        dp.reset(idx);
        while (!dp.isFull()){
            if (file_reader->peekEof())
                break;
            file_reader->read(number);
            dp.load(number);
        }
        while (!dp.isFull())
            dp.load(0);
        //dp.print();
    }
}
