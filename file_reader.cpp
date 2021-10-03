#include <iostream>
#include "file_reader.h"

file_reader::file_reader(const char * const & filename): file(filename) {
    if(!file.is_open()) {
        file.close();
        throw std::invalid_argument("el archivo no existe");
    }
    checkNativeEndianness();
}

void file_reader::read(uint8_t& byte) {
    file.read((char*) &byte, 1);
}

//chequeos
void file_reader::read(uint16_t& n, Endianness endianness){
    uint8_t bytes[2];
    read(bytes[0]);
    read(bytes[1]);
    if (endianness == native)
        n = bytes[0] + (bytes[1] << 8);
    else
        n = bytes[1] + (bytes[0] << 8);
}

void file_reader::read(uint16_t& n){
    read(n, ENDIANNESS_BIG);
}

bool file_reader::eof() {
    return file.eof();
}

file_reader::~file_reader() {
    file.close();
}

// Reemplazar con clase Endian?
void file_reader::checkNativeEndianness() {
    int num = 1;
    if(*(char *)&num == 1)
        native = ENDIANNESS_LITTLE;
    else
        native = ENDIANNESS_BIG;
}


