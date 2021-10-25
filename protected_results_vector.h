#ifndef TP2_TALLER1_PROTECTEDRESULTVECTOR_H
#define TP2_TALLER1_PROTECTEDRESULTVECTOR_H

#include <vector>
#include <mutex>
#include "result.h"

/* Clase monitor de un vector que contiene objetos de tipo
 * Result. Como atributos contiene al vector en si y a un mutex.*/
class ProtectedResultsVector {
    std::vector<Result> vector;
    std::mutex mutex;

public:
    // Constructor.
    ProtectedResultsVector();

    // Agrega un nuevo elemento al final.
    void emplace_back(const Result & result);

    // Accede al elemento idx.
    Result& operator[](size_t idx);

    // Devuelve el tamanio del vector.
    size_t size();
};


#endif //TP2_TALLER1_PROTECTEDRESULTVECTOR_H
