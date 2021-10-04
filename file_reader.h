#ifndef TP2_TALLER1_FILE_READER_H
#define TP2_TALLER1_FILE_READER_H

#include <fstream>

typedef enum{
    ENDIANNESS_BIG,
    ENDIANNESS_LITTLE
} Endianness;

class FileReader {
private:
    std::ifstream file;
    Endianness native;

    void checkNativeEndianness();

public:
    explicit FileReader(const char * const & filename);
    FileReader(FileReader& original) = delete;
    ~FileReader();
    void read(uint8_t& byte);
    void read(uint16_t& n, Endianness endianness);
    void read(uint16_t& n);
    bool eof();

    void reset();

    bool peekEof();
};




#endif //TP2_TALLER1_FILE_READER_H
