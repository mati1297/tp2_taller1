#ifndef TP2_TALLER1_FILE_READER_H
#define TP2_TALLER1_FILE_READER_H

#include <fstream>

class FileReader {
private:
    std::ifstream file;

public:
    explicit FileReader(const char * const & filename);
    FileReader(FileReader& original) = delete;
    ~FileReader();
    void read(uint8_t& byte);
    void read(uint16_t& n);
    bool eof();

    void reset();

    bool peekEof();

    void setTo(const uint32_t & position);
};




#endif //TP2_TALLER1_FILE_READER_H
