#include <iostream>
#include "result.h"

Result::Result(): number(0), extra(0), initialized(false) {}

Result::Result(const uint16_t & number): number(number), extra(0) {}

Result::Result(const uint16_t & number,
               const uint32_t & extra): number(number), extra(extra) {}

void Result::reset(){
    number = 0;
    extra = 0;
}

void Result::setNumber(const uint16_t & number_) {
    initialized = true;
    this->number = number_;
}

void Result::setExtra(const uint32_t & extra_) {
    initialized = true;
    this->extra = extra_;
}

const uint16_t & Result::getNumber() const {
    return number;
}

const uint32_t & Result::getExtra() const {
    return extra;
}

const bool Result::isInitialized() const{
    return initialized;
}
