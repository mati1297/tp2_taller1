#include "data_loader.h"
#include "data_partition.h"
#include "file_reader.h"

DataLoader::DataLoader(FileReader * const & file_reader):
                       file_reader(file_reader), start(0),
                       end(UINT32_MAX), counter(0) {}


bool DataLoader::endOfDataset() const {
    return (file_reader->eof() || counter >= (end-start));
}

void DataLoader::load(DataPartition & dp) {
    if (!file_reader->peekEof() && counter < (end - start)){
        dp.reset();
        while (!dp.isFull() && counter < (end-start)){
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

void DataLoader::setStart(const uint32_t & start_) {
    start = start_;
    file_reader->setTo(start_ * 2);
    counter = 0;
}

void DataLoader::setEnd(const uint32_t & end_) {
    end = end_;
    counter = 0;
}
