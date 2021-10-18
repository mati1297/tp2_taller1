#ifndef TP2_TALLER1_PROTECTEDRESULTVECTOR_H
#define TP2_TALLER1_PROTECTEDRESULTVECTOR_H

#include <vector>
#include <mutex>
#include "result.h"

class ProtectedResultsVector {
    std::vector<Result> vector;
    std::mutex mutex;

public:
    ProtectedResultsVector();

    void emplace_back(const Result & result);

    Result& operator[](size_t idx);

    size_t size() const;
};


#endif //TP2_TALLER1_PROTECTEDRESULTVECTOR_H
