#ifndef TP2_TALLER1_DATAPARTITION_H
#define TP2_TALLER1_DATAPARTITION_H

#include <vector>
#include <cstdint>
#include <mutex>

/* Clase protegida que representa una particion de datos que se
 * carga en memoria. Las particiones son accedidas solo por un hilo
 * al momento de cargar y procesar. Pero deben ser protegidos ciertos
 * metodos ya que al momento de la preparacion es accedida por un determinado
 * hilo y por el hilo principal.
 * Como atributos posee vectores con la informacion que contiene,
 * contadores de posicion, informacion sobre su tamano, un flag de
 * terminado e informacion sobre su estado de completitud. */
class DataPartition {
private:
    uint32_t rows;
    const uint32_t columns;
    uint32_t _row;
    uint32_t _column;
    bool closed;
    std::vector<std::vector<uint16_t>> data;
    bool done;
    std::mutex m;

public:
    // Constructor, recibe el tamanio en forma de rows y columns.
    DataPartition(const uint32_t & rows,
                  const uint32_t & columns);

    // Constructor por copia.
    DataPartition(const DataPartition & orig);

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

    // Devuelve la cantidad de filas de la particion.
    const uint32_t & getRows() const;

    // Setea el flag done segun done_.
    void setDone(bool done_);

    // Devuelve el flag done.
    bool isDone();
};


#endif //TP2_TALLER1_DATAPARTITION_H
