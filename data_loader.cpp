#include "data_loader.h"
#include "data_partition.h"
#include "file_reader.h"

DataLoader::DataLoader(): file_reader(), start(0),
                       end(UINT32_MAX), counter(0), m() {}

void DataLoader::openFile(const char * const & filename) {
    try{
        file_reader.open(filename);
    }
    catch(std::exception & e){
        throw;
    }
}

bool DataLoader::unlockedEndOfDataset() {
    return (file_reader.eof() || file_reader.peekEof()
            || counter >= (end-start));
}

bool DataLoader::endOfDataset() {
    m.lock();
    bool ret = unlockedEndOfDataset();
    m.unlock();
    return ret;
}

void DataLoader::load(DataPartition & dp) {
    // Se resetea el DataPartition.
    dp.reset();
    // Mientras que la particion no este llena y el contador
    // este en rango se lee.
    while (!dp.isClosed() && counter < (end - start)){
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
        // Se incrementa el contador de datos leidos.
        counter++;
    }
    // Se cierra la particion de datos tras leer (este llena o no).
    dp.close();
}

bool DataLoader::ifDatasetNotEndedLoad(DataPartition & dp) {
    // Se bloquea el mutex.
    m.lock();
    // Si se llego al final del dataset no se hace nada.
    if (unlockedEndOfDataset()) {
        m.unlock();
        return false;
    }
    // Si todavia queda por leer se carga.
    load(dp);
    m.unlock();
    return true;
}


void DataLoader::setStart(const uint32_t & start_) {
    m.lock();
    start = start_;
    file_reader.setTo(start_ * 2);
    counter = 0;
    m.unlock();
}

void DataLoader::setEnd(const uint32_t & end_) {
    m.lock();
    end = end_;
    counter = 0;
    m.unlock();
}


