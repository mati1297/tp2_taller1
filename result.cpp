#include <iostream>
#include <string>
#include "result.h"
#include "operator.h"

Result::Result(): number(0), extra(0), initialized(false),
                  mutex(), separator("") {}

Result::Result(const Result & orig): number(orig.number), extra(orig.extra),
                                     initialized(orig.initialized), mutex(),
                                     separator(orig.separator) {}

void Result::reset(){
    mutex.lock();
    // Se setean todos los valores a false y 0.
    initialized = false;
    number = 0;
    extra = 0;
    separator = "";
    mutex.unlock();
}

void Result::setNumber(const uint16_t & number_) {
    mutex.lock();
    // Se setea inicializado a true y se guarda el numero.
    initialized = true;
    this->number = number_;
    mutex.unlock();
}

void Result::setExtra(const uint32_t & extra_) {
    mutex.lock();
    // Se setea inicializado a true y se guarda el extra.
    initialized = true;
    this->extra = extra_;
    mutex.unlock();
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
    mutex.lock();
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
    mutex.unlock();
}

const uint16_t & Result::getNumber() const {
    return number;
}

const uint32_t & Result::getExtra() const {
    return extra;
}

std::ostream& operator<<(std::ostream& os, const Result & result) {
    if (result.separator == "")
        os << result.number;
    else
        os << result.number << result.separator << result.extra;
    return os;
}





