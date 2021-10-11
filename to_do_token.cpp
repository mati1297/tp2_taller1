#include "to_do_token.h"

ToDoToken::ToDoToken(): idx(0), end(false) {}

ToDoToken::ToDoToken(const uint32_t & idx_, const bool & end_):
        idx(idx_), end(end_) {}

bool ToDoToken::endOfWork() const {
    return end;
}

const uint32_t & ToDoToken::getIndex() const {
    return idx;
}

ToDoToken& ToDoToken::operator=(const ToDoToken & orig) {
    this->end = orig.end;
    this->idx = orig.idx;
    return *this;
}


