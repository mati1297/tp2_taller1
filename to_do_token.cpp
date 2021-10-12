#include "to_do_token.h"

ToDoToken::ToDoToken(): end(false), op(nullptr), result_idx(0),
                        part_rows(0), from(0), to(0),
                        column_to_process(0) {}

ToDoToken::ToDoToken(const bool & end_, const Operator * const & op_,
                     const size_t & result_idx_, const uint32_t & part_rows_,
                     const uint32_t & from, const uint32_t & to,
                     const uint32_t & column_to_process_):
        end(end_), op(op_), result_idx(result_idx_),
        part_rows(part_rows_), from(from),
        to(to), column_to_process(column_to_process_) {}

ToDoToken::ToDoToken(const bool & end_): end(end_), op(nullptr), result_idx(0),
                                         part_rows(0), from(0), to(0),
                                         column_to_process(0) {}

bool ToDoToken::endOfWork() const {
    return end;
}

const Operator * const & ToDoToken::getOperator() const {
    return op;
}

const size_t & ToDoToken::getResultIndex() const {
    return result_idx;
}

const uint32_t & ToDoToken::getPartitionRows() const {
    return part_rows;
}

const uint32_t & ToDoToken::getFrom() const {
    return from;
}

const uint32_t & ToDoToken::getTo() const {
    return to;
}

const uint32_t & ToDoToken::getColumnToProcess() const {
    return column_to_process;
}

ToDoToken& ToDoToken::operator=(const ToDoToken & orig) {
    this->end = orig.end;
    this->op = orig.op;
    this->result_idx = orig.result_idx;
    this->part_rows = orig.part_rows;
    this->from = orig.from;
    this->to = orig.to;
    this->column_to_process = orig.column_to_process;
    return *this;
}


