#include <cstdint>
#include <vector>
#include <iostream>
#include "operator.h"
#include "result.h"

void Operator::operate(Result & result, const std::vector<uint16_t> & data) const{
    operate(result, data, 0, data.size());
}

void Operator::operate(Result & result, const std::vector<Result> & data) const {
    std::vector<uint16_t> _data = std::vector<uint16_t>(data.size());
    for (uint32_t i = 0; i < _data.size(); i++)
        _data[i] = data[i].getNumber();
    operate(result, _data);
}

void Operator::printResult(Result & result) const {
    std::cout << result.getNumber() << std::endl;
}
