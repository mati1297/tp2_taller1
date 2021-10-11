#include <iostream>
#include "result.h"
#include "operator.h"

Result::Result(): number(0), extra(0), initialized(false), mutex() {}

Result::Result(const Result & orig) {
    number = orig.number;
    extra = orig.extra;
}

void Result::reset(){
    mutex.lock();
    initialized = false;
    number = 0;
    extra = 0;
    mutex.unlock();
}

void Result::setNumber(const uint16_t & number_) {
    mutex.lock();
    initialized = true;
    this->number = number_;
    mutex.unlock();
}

void Result::accumulate(const Result & result_, const Operator * const & op) {
    accumulate(result_.getNumber(), result_.getExtra(), op);
}

void Result::accumulate(const uint16_t & number_, const uint32_t & extra_,
                        const Operator * const & op) {
    mutex.lock();
    if (initialized) {
        op->operate(number, number_);
        op->operateExtra(extra, extra_);
    } else {
        number = number_;
        extra = extra_;
        initialized = true;
    }
    mutex.unlock();
}

void Result::setExtra(const uint32_t & extra_) {
    mutex.lock();
    initialized = true;
    this->extra = extra_;
    mutex.unlock();
}

const uint16_t & Result::getNumber() const {
    return number;
}

const uint32_t & Result::getExtra() const {
    return extra;
}



