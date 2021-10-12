#ifndef TP2_TALLER1_FILE_READER_H
#define TP2_TALLER1_FILE_READER_H

#include <fstream>

/* Clase que permite manejar archivos y leer desde ellos
 * valores numericos. */
class FileReader {
private:
    std::ifstream file;

public:
    // Constructor sin parametros.
    FileReader();

    // Se borra el constructor por copia.
    FileReader(FileReader & original) = delete;

    // Se borra el constructor por movimiento.
    FileReader(FileReader && orig) = delete;

    // Destructor.
    ~FileReader();

    /* Metodo que permite abrir un archivo, cerrando el
     * actual si hubiese uno abierto. */
    void open(const char *const &filename);

    // Metodo que cierra el archivo actual si hubiese uno abierto.
    void close();

    // Metodo que permite leer un byte desde el archivo.
    void read(uint8_t& byte);

    /* Metodo que permite leer un numero no signado de 16 bits
     * en formato big endian. */
    void read(uint16_t& n);

    // Devuelve true si se alcanzo el end of file.
    bool eof();

    // Devuelve true si el proximo caracter a leer es end of file.
    bool peekEof();

    // Setea el lector al principio del archivo.
    void reset();

    /* Setea el lector a una determinada posicion desde el principio
     * del archivo. */
    void setTo(const uint32_t & position);
};




#endif //TP2_TALLER1_FILE_READER_H
