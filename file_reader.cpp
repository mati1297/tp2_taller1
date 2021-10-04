#include <iostream>
#include "file_reader.h"

FileReader::FileReader(const char * const & filename): file(filename) {
    if (!file.is_open()) {
        file.close();
        throw std::invalid_argument("el archivo no existe");
    }
    checkNativeEndianness();
}

void FileReader::reset(){
    file.clear();
    file.seekg(0, std::ios_base::beg);
}

void FileReader::read(uint8_t& byte) {
    file.read((char*) &byte, 1);
}

//chequeos
void FileReader::read(uint16_t& n, Endianness endianness){
    uint8_t bytes[2];
    read(bytes[0]);
    read(bytes[1]);
    if (endianness == native)
        n = bytes[0] + (bytes[1] << 8);
    else
        n = bytes[1] + (bytes[0] << 8);
}

void FileReader::read(uint16_t& n){
    read(n, ENDIANNESS_BIG);
}

bool FileReader::eof() {
    return file.eof();
}

bool FileReader::peekEof() {
    return (file.peek() == EOF);
}

FileReader::~FileReader() {
    file.close();
}

// Reemplazar con clase Endian?
void FileReader::checkNativeEndianness() {
    int num = 1;
    if (*(char *)&num == 1)
        native = ENDIANNESS_LITTLE;
    else
        native = ENDIANNESS_BIG;
}




