#include "to_do_token.h"

ToDoToken::ToDoToken(): end(true), op(nullptr), dp(0, 0), result_idx(0),
                        column_to_process(0) {}

ToDoToken::ToDoToken(const bool & end_, const Operator * op_,
                     const DataPartition & dp_, const size_t & result_idx_,
                     const uint32_t & column_to_process_):
        end(end_), op(op_), dp(dp_), result_idx(result_idx_),
        column_to_process(column_to_process_) {}

bool ToDoToken::endOfWork() const {
    return end;
}

const DataPartition & ToDoToken::getDataPartition() const {
    return dp;
}

const Operator * const & ToDoToken::getOperator() const {
    return op;
}

const size_t & ToDoToken::getResultIndex() const {
    return result_idx;
}

const uint32_t & ToDoToken::getColumnToProcess() const {
    return column_to_process;
}



