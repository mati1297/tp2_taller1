#ifndef TP2_TALLER1_DATA_LOADER_H
#define TP2_TALLER1_DATA_LOADER_H


#include <mutex>
#include <fstream>
#include "data_partition.h"

/* Clase que permite cargar los datos desde un archivo en las
 * particiones de datos. Contiene como atributos un ifstream, variables
 * que contienen desde y hasta donde se debe leer y un contador de bytes
 * leidos. */
class DataLoader {
    std::ifstream file;
    uint32_t from;
    uint32_t to;
    uint32_t counter;

public:
    // Constructor. Se le pasa el nombre del archivo.
    explicit DataLoader(const char * filename);

    // Se borra el constructor por copia
    DataLoader(const DataLoader & orig) = delete;

    // Se borra el constructor por movimiento
    DataLoader(DataLoader && orig) = delete;

    // Se borra el operador =
    DataLoader & operator=(const DataLoader & orig) = delete;

    /* Metodo que lee la cantidad de bytes que corresponden para llenar a la
     * DataPartition y mientras se lo permita sus limites. */
    void load(DataPartition & dp);

    /* Metodo que setea los limites en donde se debe leer del archivo
     * y resetea el contador. */
    void setLimits(const uint32_t &from_, const uint32_t &to_);
};

#endif //TP2_TALLER1_DATA_LOADER_H
