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
    void read(uint16_t& n, bool is_little_endian);
    void read(uint16_t& n);
    bool eof();

    void reset();

    bool peekEof();

    void setTo(size_t position);
};




#endif //TP2_TALLER1_FILE_READER_H
