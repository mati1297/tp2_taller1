#include "protected_results_vector.h"
#include <vector>
#include <mutex>
#include "result.h"

ProtectedResultsVector::ProtectedResultsVector(): vector(), mutex() {}

void ProtectedResultsVector::emplace_back(const Result & result) {
    std::lock_guard<std::mutex> lock(mutex);
    vector.emplace_back(result);
}

Result& ProtectedResultsVector::operator[](size_t idx) {
    std::lock_guard<std::mutex> lock(mutex);
    return vector[idx];
}

size_t ProtectedResultsVector::size() {
    std::lock_guard<std::mutex> lock(mutex);
    return vector.size();
}
