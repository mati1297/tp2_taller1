#ifndef TP2_TALLER1_SPLITAPPLYCOMBINE_H
#define TP2_TALLER1_SPLITAPPLYCOMBINE_H

#include "file_reader.h"
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"

class SplitApplyCombine {
    FileReader file_reader;
    DataLoader data_loader;

    void loadAndValidate(const char * const dataset_filename,
                         const std::string & text_columns, const std::string & text_workers,
                         uint32_t & columns, uint8_t & workers);

public:
    SplitApplyCombine();

    void execute(const char * const dataset_filename,
                                    const std::string & text_columns, const std::string & text_workers);
};


#endif //TP2_TALLER1_SPLITAPPLYCOMBINE_H
