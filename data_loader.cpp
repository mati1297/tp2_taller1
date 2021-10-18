#include <iostream>
#include <netinet/in.h>
#include "data_loader.h"
#include "data_partition.h"

DataLoader::DataLoader(const char * filename): file(filename),
                                               from(0), to(0) {
    if (!file.is_open())
        throw std::invalid_argument("el archivo no existe");
}

void DataLoader::load(DataPartition & dp) {
    if (file.peek() == EOF || !file || counter >= (from - to))
        return;
    dp.reset();
    while (!dp.isClosed() && counter < (to - from)){
        if (file.peek() == EOF || !file)
            break;
        uint16_t number;
        file.read((char*) &number, 2);
        number = ntohs(number);
        dp.load(number);
        counter++;
    }
    dp.close();
}

void DataLoader::setLimits(const uint32_t & from_, const uint32_t & to_) {
    if (from_ > to_)
        throw std::invalid_argument("el limite superior es mayor al inferior");
    from = from_;
    to = to_;
    file.seekg(from_ * 2, std::ios::beg);
    counter = 0;
}



