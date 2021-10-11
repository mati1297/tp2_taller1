//
// Created by matias on 7/10/21.
//

#include "to_do_token.h"

ToDoToken::ToDoToken(uint32_t idx_, bool end_): idx(idx_), end(end_) {}

bool ToDoToken::endOfWork() const {
    return end;
}

const uint32_t & ToDoToken::getIndex() const {
    return idx;
}

const ToDoToken& ToDoToken::operator=(const ToDoToken & orig) {
    this->end = orig.end;
    this->idx = orig.idx;
    return *this;
}

ToDoToken::ToDoToken(): idx(0), end(false) {}
