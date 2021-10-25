#include "protected_results_vector.h"
#include <vector>
#include <mutex>
#include <iostream>
#include "result.h"

ProtectedResultsVector::ProtectedResultsVector(): vector(), mutex() {}

void ProtectedResultsVector::emplace_back(const Result & result) {
    std::lock_guard<std::mutex> lock(mutex);
    vector.emplace_back(result);
}

void ProtectedResultsVector::accumulate(size_t idx,
                                        const Operator * op, Result & result) {
    std::lock_guard<std::mutex> lock(mutex);
    op->accumulate(vector[idx], result);
}


std::ostream & operator<<(std::ostream &os, ProtectedResultsVector &vector) {
    std::lock_guard<std::mutex> lock(vector.mutex);
    for (size_t i = 0; i < vector.vector.size(); i++)
        os << vector.vector[i] << std::endl;
    return os;
}
