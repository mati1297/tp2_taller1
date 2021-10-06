//
// Created by matias on 4/10/21.
//

#include <iostream>
#include "result.h"

Result::Result(): number(0), extra(0) {}

Result::Result(uint16_t number): number(number), extra(0) {}

Result::Result(uint16_t number, size_t extra): number(number), extra(extra) {}

void Result::reset(){
    number = 0;
    extra = 0;
}

void Result::setNumber(uint16_t number) {
    this->number = number;
}

void Result::setExtra(size_t extra) {
    this->extra = extra;
}

const uint16_t &Result::getNumber() const {
    return number;
}

const size_t& Result::getExtra() const {
    return extra;
}
