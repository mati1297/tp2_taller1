//
// Created by matias on 2/10/21.
//

#include <iostream>
#include <cmath>
#include "operator.h"
#include "data_partition.h"

::(size_t column, size_t rows, size_t index_from, size_t index_to): column(column), rows(rows), index_from(index_from), index_to(index_to), results(std::ceil((double(index_to) - double(index_from))/2)) {}

void ::apply(data_partition& dp){
    /*
    if(dp.getFirstRowIndex() >= index_from && dp.getLastRowIndex() < index_to){
        size_t idx = dp.getIndex();
        std::vector<uint16_t> column_data = dp.getColumnData(column);
        uint16_t result = operate(column_data);
        results[idx - index_from] = result;
    }
     */
    //CHEQUEO DE SI LA CANTIDAD DE ROWS ES LA MISMA, SINO ERROR.
    int dp_from = std::max(index_from, dp.getFirstRowIndex()) - dp.getFirstRowIndex();
    int dp_to = std::min(index_to - 1, dp.getLastRowIndex()) - dp.getFirstRowIndex() + 1;// + dp.getRowsCant()%2;
    if(dp_to > dp_from){
        size_t idx = dp.getIndex();
        const std::vector<uint16_t>& column_data = dp.getColumnData(column);
        uint16_t result = operate(column_data, dp_from, dp_to);
        results[idx - index_from / rows] = result;
    }
}

uint16_t ::combine() const {
    return operate(results);
}

uint16_t ::operate(const std::vector<uint16_t>& data) const{
    return operate(data, 0, data.size());
}





