#include <iostream>
#include <netinet/in.h>
#include "data_loader.h"
#include "data_partition.h"

DataLoader::DataLoader(const char * filename): file(filename),
                                               end_position(0),
                                               position(0), m() {
    if (!file.is_open())
        throw std::invalid_argument("el archivo no existe");
    file.seekg(0, std::ios_base::end);
    end_position = file.tellg();
    file.seekg(0, std::ios_base::beg);
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
        if (file.peek() == EOF)
            break;
        // Se lee el numero.
        file.read((char*) &number, 2);
        number = ntohs(number);
        // Se intenta cargar, si falla se lanza la excepcion atrapada.
        dp.load(number);
        // Se incrementa la posicion.
        position++;
    }
    // Se cierra la particion de datos tras leer (este llena o no).
    dp.close();
}

void DataLoader::unlockedSetPosition(const uint32_t & start_) {
    file.seekg(start_ * 2, std::ios_base::beg);
    position = start_;
}



