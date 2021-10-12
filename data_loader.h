#ifndef TP2_TALLER1_DATA_LOADER_H
#define TP2_TALLER1_DATA_LOADER_H


#include <mutex>
#include "file_reader.h"
#include "data_partition.h"

/* Clase protegida que permite cargar los datos desde un archivo en las
 * particiones de datos. Contiene como atributos un FileReader, un contador
 * y desde y hasta donde se debe leer del archivo. La clase es protegida
 * ya que es accedida por los distintos hilos al mismo tiempo. */
class DataLoader {
    FileReader file_reader;
    uint32_t end_position;
    uint32_t position; // Contador de datos leidos (cada 2 bytes)
    std::mutex m;

    void unlockedSetPosition(const uint32_t &start_);

public:
    // Constructor.
    DataLoader();

    // Metodo que abre un archivo para utilizar como dataset.
    void openFile(const char * const & filename);

    void load(DataPartition & dp, const uint32_t & start, const uint32_t & end);
};

#endif //TP2_TALLER1_DATA_LOADER_H
