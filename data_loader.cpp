//
// Created by matias on 4/10/21.
//

#include "data_loader.h"
#include "file_reader.h"

DataLoader::DataLoader(FileReader * const file_reader):
                       file_reader(file_reader), start(0),
                       end(UINT64_MAX), counter(0) {}


bool DataLoader::endOfDataset(){
    return (file_reader->eof() or counter >= (end-start));
}

void DataLoader::load(DataPartition &dp, const size_t& idx){
    if (!file_reader->peekEof() and counter < (end - start)){
        dp.reset(idx);
        while (!dp.isFull()){
            uint16_t number;
            if (file_reader->peekEof())
                break;
            file_reader->read(number);
            try {
                dp.load(number);
            }
            catch(std::length_error& e){
                throw;
            }
            counter++;
        }
        dp.close();
        //dp.print();
    }
}

void DataLoader::setStart(const size_t& _start) {
    start = _start;
    file_reader->setTo(_start * 2);
    counter = 0;
}

void DataLoader::setEnd(const size_t& _end) {
    end = _end;
    counter = 0;
}
