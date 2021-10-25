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

    /* Permite acumular en el result del index pasado como parametro.
     * el valor del result pasado, utilizando la operacion op. */
    void accumulate(size_t idx, const Operator * op, Result & result);

    friend std::ostream & operator<<(std::ostream & os,
            ProtectedResultsVector & vector);
};


#endif //TP2_TALLER1_PROTECTEDRESULTVECTOR_H
