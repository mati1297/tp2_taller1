//
// Created by matias on 7/10/21.
//

#ifndef TP2_TALLER1_TO_DO_TOKEN_H
#define TP2_TALLER1_TO_DO_TOKEN_H


#include "data_partition.h"

class ToDoToken {
    uint32_t idx;
    bool end;


public:
    ToDoToken();

    ToDoToken(uint32_t idx_, bool end_);

    ToDoToken& operator=(const ToDoToken &);

    const uint32_t & getIndex() const;

    bool endOfWork() const;
};


#endif //TP2_TALLER1_TO_DO_TOKEN_H