#include <iostream>
#include <string>
#include "result.h"
#include "operator.h"

Result::Result(): number(0), extra(0), initialized(false),
                  mutex(), separator("") {}

Result::Result(const Result & orig): number(orig.number), extra(orig.extra),
                                     initialized(orig.initialized), mutex(),
                                     separator(orig.separator) {}

Result & Result::operator= (const Result & orig){
    number = orig.number;
    extra = orig.extra;
    initialized = orig.initialized;
    separator = orig.separator;
    return *this;
}


void Result::reset(){
    // Se utiliza lock guard, que utiliza RAII.
    std::lock_guard<std::mutex> lock_guard(mutex);
    // Se setean todos los valores a false y 0.
    initialized = false;
    number = 0;
    extra = 0;
    separator = "";
}

void Result::setNumber(const uint16_t & number_) {
    // Se utiliza lock guard, que utiliza RAII.
    std::lock_guard<std::mutex> lock_guard(mutex);
    // Se setea inicializado a true y se guarda el numero.
    initialized = true;
    this->number = number_;
}

void Result::setExtra(const uint32_t & extra_) {
    // Se utiliza lock guard, que utiliza RAII.
    std::lock_guard<std::mutex> lock_guard(mutex);
    // Se setea inicializado a true y se guarda el extra.
    initialized = true;
    this->extra = extra_;
}

void Result::setSeparator(const std::string & separator_) {
    initialized = true;
    separator = separator_;
}

void Result::accumulate(const Result & result_, const Operator * const & op) {
    accumulate(result_.getNumber(), result_.getExtra(), op);
}

void Result::accumulate(const uint16_t & number_, const uint32_t & extra_,
                        const Operator * const & op) {
    // Se utiliza lock guard, que utiliza RAII.
    std::lock_guard<std::mutex> lock_guard(mutex);
    // Si esta inicializado se acumula.
    if (initialized) {
        op->accumulate(number, number_);
        op->accumulateExtra(extra, extra_);
    } else {
        // Si no, se inicializan los atributos.
        number = number_;
        extra = extra_;
        initialized = true;
        separator = op->getSeparator();
    }
}

const uint16_t & Result::getNumber() const {
    return number;
}

const uint32_t & Result::getExtra() const {
    return extra;
}

std::ostream& operator<<(std::ostream& os, const Result & result) {
    if (result.separator.empty())
        os << result.number;
    else
        os << result.number << result.separator << result.extra;
    return os;
}





