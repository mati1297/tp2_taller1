#include <iostream>
#include "data_loader.h"
#include "data_partition.h"
#include "file_reader.h"

DataLoader::DataLoader(): file_reader(), end_position(0), position(0), m() {}

void DataLoader::openFile(const char * const & filename) {
    try{
        file_reader.open(filename);
    }
    catch(std::exception & e){
        throw;
    }
    end_position = file_reader.positionOfEnd() / 2;
}

void DataLoader::load(DataPartition & dp, const uint32_t & start,
                      const uint32_t & end) {
    // Se bloquea utilizando un lock guard (que usa RAII).
    std::lock_guard<std::mutex> lock_guard(m);
    // Se resetea el DataPartition.
    dp.reset();
    // Si se comienza antes del final, se setea la posicion. Sino se retorna.
    if (start < end_position)
        unlockedSetPosition(start);
    else
        return;

    /* Mientras que la data partition no este cerrada, no se alcance el final
     * de la lectura ni del archivo, se lee de a 2 bytes (uint16_t). */
    while (!dp.isClosed() && position < end_position && position < end){
        uint16_t number;
        // Si se alcanzo end of file se rompe el ciclo.
        if (file_reader.peekEof())
            break;
        // Se lee el numero.
        file_reader.read(number);
        // Se intenta cargar, si falla se lanza la excepcion atrapada.
        try {
            dp.load(number);
        }
        catch(std::length_error& e){
            throw;
        }
        // Se incrementa la posicion.
        position++;
    }
    // Se cierra la particion de datos tras leer (este llena o no).
    dp.close();
}

void DataLoader::unlockedSetPosition(const uint32_t & start_) {
    file_reader.setTo(start_ * 2);
    position = start_;
}



