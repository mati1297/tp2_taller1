#include "split_apply_combine.h"
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "data_loader.h"
#include "task.h"
#include "task_reader.h"
#include "to_do_queue.h"
#include "worker.h"
#include "protected_results_vector.h"

SplitApplyCombine::SplitApplyCombine(const char * const dataset_filename,
                                     const std::string & text_columns,
                                     const std::string & text_workers):
                                 workers(validateAndConvert(text_workers)),
                                 part_columns(validateAndConvert(text_columns)),
                                 data_loader(dataset_filename), queue(workers),
                                 results_vector(), workers_vector(workers,
                                 Worker(queue, results_vector, part_columns)),
                                 threads_vector(workers) {}

void SplitApplyCombine::execute() {
    // Se lanzan los threads, asignandole un worker a cada uno.
    for (uint8_t i = 0; i < workers; i++)
        threads_vector[i] = std::thread(workers_vector[i]);

    // Se crea el Task Reader.
    TaskReader task_reader;

    // Se realiza un loop hasta que termine la entrada.
    for (size_t i = 0; std::cin.peek() != EOF && !std::cin.eof(); i++) {
        // Se lee la entrada y se carga en la task.
        try {
            // Si no se leyo se rompe el ciclo.
            Task task = task_reader.read(task, part_columns);
            // Se crea un nuevo resultado.
            results_vector.emplace_back(Result());
            // Se carga la cola con los quehaceres correspondientes a la tarea.
            task.loadQueue(queue, data_loader, i);
        }
        catch(std::exception &e){
            // Si falla se terminan los hilos y se termina el programa.
            endAndJoin();
            throw;
        }
    }
    // Se terminan y joinean los hilos.
    endAndJoin();

    // Se imprimen los resultados.
    std::cout << results_vector;
}

void SplitApplyCombine::endAndJoin(){
    for (uint8_t i = 0; i < workers; i++) {
        ToDoToken end_token;
        queue.push(end_token);
    }

    for (uint8_t i = 0; i < workers; i++)
        threads_vector[i].join();
}


uint32_t SplitApplyCombine::validateAndConvert(const std::string & text){
    if (text.find('-') != std::string::npos)
        throw std::invalid_argument("numero negativo");

    return std::stoul(text);
}
