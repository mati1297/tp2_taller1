#include <iostream>
#include "result.h"
#include "operator.h"

Result::Result(): number(0), extra(0), initialized(false), mutex() {}

Result::Result(const Result & orig): number(orig.number), extra(orig.extra) {}

void Result::reset(){
    mutex.lock();
    // Se setean todos los valores a false y 0.
    initialized = false;
    number = 0;
    extra = 0;
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
    }
    mutex.unlock();
}

const uint16_t & Result::getNumber() const {
    return number;
}

const uint32_t & Result::getExtra() const {
    return extra;
}



