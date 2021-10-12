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
    uint32_t start; // Posicion en la que se arranca (cada 2 bytes)
    uint32_t end; // Posicion en la que se arranca (cada 2 bytes)
    uint32_t counter; // Contador de datos leidos (cada 2 bytes)
    std::mutex m;

    // Metodo privado que permite cargar datos en una particion.
    void load(DataPartition & dp);

    // Metodo privado para obtener end of dataset sin bloquear el mutex.
    bool unlockedEndOfDataset();

public:
    // Constructor.
    DataLoader();

    // Metodo que abre un archivo para utilizar como dataset.
    void openFile(const char * const & filename);

    /* Metodo que permite cargar la particion de datos dp si
     * el dataset no termino. */
    bool ifDatasetNotEndedLoad(DataPartition & dp);

    /* Metodo que devuelve true si el dataset termino. Esto puede
     * ser ya porque se alcanzo eof (o el siguiente caracter lo es)
     * o porque se alcanzo el limite correspondiente a lo que se debe
     * leer. */
    bool endOfDataset();

    // Metodo que permite setear donde se inicia la lectura.
    void setStart(const uint32_t & start_);

    // Metodo que permite setear donde se termina la lectura.
    void setEnd(const uint32_t & end_);
};

#endif //TP2_TALLER1_DATA_LOADER_H
