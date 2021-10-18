#ifndef TP2_TALLER1_DATA_LOADER_H
#define TP2_TALLER1_DATA_LOADER_H


#include <mutex>
#include <fstream>
#include "data_partition.h"

/* Clase protegida que permite cargar los datos desde un archivo en las
 * particiones de datos. Contiene como atributos un FileReader, una variable
 * que guarda la posicion en que se encuentra del archivo, una variable
 * con la posicion final del archivo, y un mutex. */
class DataLoader {
    std::ifstream file;
    uint32_t end_position; // Posicion final del archivo (de a 2 bytes).
    uint32_t position; // Posicion en el archivo (de a 2 bytes)
    std::mutex m;

    // Modifica la posicion en que se encuentra en el archivo, no bloquea.
    void unlockedSetPosition(const uint32_t &start_);

public:
    // Constructor. Se le pasa el nombre del archivo.
    explicit DataLoader(const char * filename);

    // Se borra el constructor por copia
    DataLoader(const DataLoader & orig) = delete;

    // Se borra el constructor por movimiento
    DataLoader(DataLoader && orig) = delete;

    // Se borra el operador =
    DataLoader & operator=(const DataLoader & orig) = delete;

    /* Metodo protegido que lee el archivo desde la posicion (de a 2 bytes)
     * inicial hasta la final y guarda en la particion de datos. */
    void load(DataPartition & dp, const uint32_t & start, const uint32_t & end);
};

#endif //TP2_TALLER1_DATA_LOADER_H
