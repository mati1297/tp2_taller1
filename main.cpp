#include <iostream>
#include "file_reader.h"
#include "data_loader.h"
#include "data_partition.h"
#include "task.h"
#include "task_reader.h"
#include "split_apply_combine.h"

int main(int argc, char * argv[]) {
    if (argc != 4) {
        std::cerr << "Error: numero de argumentos invalido" << std::endl;
        return EXIT_FAILURE;
    }

    SplitApplyCombine split_apply_combine;

    try {
        split_apply_combine.execute(argv[1], argv[2], argv[3]);
    }
    catch(std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
