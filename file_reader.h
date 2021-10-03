#ifndef TP2_TALLER1_FILE_READER_H
#define TP2_TALLER1_FILE_READER_H

#include <fstream>

typedef enum{
    ENDIANNESS_BIG,
    ENDIANNESS_LITTLE
} Endianness;

class file_reader {
private:
    std::ifstream file;
    Endianness native;

    void checkNativeEndianness();

public:
    file_reader(const char * const & filename);
    file_reader(file_reader& original) = delete;
    ~file_reader();
    void read(uint8_t& byte);
    void read(uint16_t& n, Endianness endianness);
    void read(uint16_t& n);
    bool eof();
};




#endif //TP2_TALLER1_FILE_READER_H
