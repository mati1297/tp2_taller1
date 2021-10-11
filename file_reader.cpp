#include <iostream>
#include <netinet/in.h>
#include "file_reader.h"

FileReader::FileReader(): file() {}

void FileReader::open(const char * const & filename) {
    // Si hay un archivo abierto se cierra.
    if (file.is_open()){
        file.close();
    }
    // Se abre el archivo
    file.open(filename);
    // Si no se pudo abrir, se lanza una excepcion.
    if (!file.is_open()) {
        file.close();
        throw std::invalid_argument("el archivo no existe");
    }
}

void FileReader::close() {
    if (file.is_open())
        file.close();
}

void FileReader::reset() {
    file.clear();
    file.seekg(0, std::ios_base::beg);
}

void FileReader::read(uint8_t& byte) {
    file.read((char*) &byte, 1);
}

void FileReader::read(uint16_t& n){
    uint8_t bytes[2];
    read(bytes[0]);
    read(bytes[1]);
    n = bytes[0] + (bytes[1] << 8);
    n = ntohs(n);
}

bool FileReader::eof() {
    return file.eof();
}

bool FileReader::peekEof() {
    return (file.peek() == EOF);
}

FileReader::~FileReader() {
    close();
}

void FileReader::setTo(const uint32_t & position) {
    file.seekg(position, std::ios_base::beg);
}




