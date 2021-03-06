#ifndef TP2_TALLER1_DATAPARTITION_H
#define TP2_TALLER1_DATAPARTITION_H

#include <vector>
#include <cstdint>
#include <mutex>

/* Clase que representa una particion de datos que se
 * carga en memoria. Como atributos posee vectores con la 
 * informacion que contiene,contadores de posicion, informacion 
 * sobre su tamano, un flag determinado e informacion sobre 
 * su estado de completitud. */
class DataPartition {
private:
    uint32_t rows;
    uint32_t columns;
    uint32_t _row;
    uint32_t _column;
    bool closed;
    std::vector<std::vector<uint16_t>> data;

public:
    // Constructor, recibe el tamanio en forma de rows y columns.
    DataPartition(const uint32_t & rows,
                  const uint32_t & columns);

    DataPartition(const DataPartition & orig) = delete;

    DataPartition(DataPartition && orig) noexcept;

    DataPartition& operator=(DataPartition && orig) noexcept;

    // Carga un numero en la siguiente posicion de la particion.
    void load(const uint16_t & number);

    // Devuelve true si la particion se puede seguir cargando.
    bool isClosed() const;

    // Resetea la particion, incluyendo sus contadores y estado.
    void reset();

    // Devuelve una referencia a la columna correspondiente a column_idx.
    const std::vector<uint16_t> &getColumnData(const uint32_t
                                                & column_idx) const;

    // Cierra la particion.
    void close();

    // Devuelve la cantidad de filas ocupadas de la particion.
    const uint32_t & getFullRows() const;
};

#endif //TP2_TALLER1_DATAPARTITION_H
