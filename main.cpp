#include <iostream>
#include "split_apply_combine.h"

int main(int argc, char * argv[]) {
    if (argc != 4) {
        std::cerr << "Error: numero de argumentos invalido" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        SplitApplyCombine split_apply_combine(argv[1], argv[2], argv[3]);
        split_apply_combine.execute();
    }
    catch(std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
