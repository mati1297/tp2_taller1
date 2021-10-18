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


SplitApplyCombine::SplitApplyCombine(): data_loader() {}

void SplitApplyCombine::execute(const char * const dataset_filename,
                         const std::string & text_columns,
                         const std::string & text_workers) {
    uint32_t part_columns = 0;
    uint8_t workers_cant = 0;

    /* Se validan los datos ingresados, se abre el archivo, y se convierten
     * a datos numericos las columnas y workers_cant. */
    try {
        loadAndValidate(dataset_filename, text_columns,
                        text_workers, part_columns, workers_cant);
    }
    catch(std::exception & e) {
        throw;
    }

    // Se inicializa la lista, el vector de resultados y el vector de workers.
    ToDoQueue queue;
    std::vector<Result> results(0);
    std::vector<Worker> workers_vector(workers_cant,
                                       Worker(queue,
                                              data_loader,
                                              results, part_columns));

    // Se crea el vector de threads, pero todavia no se lanzan.
    std::vector<std::thread> threads_vector(workers_cant);

    // Se lanzan los threads, asignandole un worker a cada uno.
    for (uint8_t i = 0; i < workers_cant; i++)
        threads_vector[i] = std::thread(workers_vector[i]);

    // Se crea una task y el task reader.
    Task task(part_columns);
    TaskReader task_reader;

    // Se realiza un loop infinito hasta que termine la entrada.
    for (size_t i = 0; true ; i++) {
        // Se lee la entrada y se carga en la task.
        try {
            // Si no se leyo se rompe el ciclo.
            if (!task_reader.read(task))
                break;
            // Se crea un nuevo resultado.
            results.emplace_back(Result());
        }
        catch(std::exception &e) {
            // Si falla se terminan los hilos y se termina el programa.
            endAndJoin(workers_cant, threads_vector, queue);
            std::string msg = e.what();
            throw std::invalid_argument("Error al leer la tarea: " + msg);
        }
        // Se carga la cola con los quehaceres correspondientes a la tarea.
        try {
            task.loadQueue(queue, i);
        }
        catch(std::exception &e){
            // Si falla se terminan los hilos y se termina el programa.
            endAndJoin(workers_cant, threads_vector, queue);
            std::string msg = e.what();
            throw std::invalid_argument("Error al correr la tarea: " + msg);
        }
    }

    endAndJoin(workers_cant, threads_vector, queue);

    // Se imprimen los de todas las tareas realizadas.
    for (size_t i = 0; i < results.size(); i++){
        std::cout << results[i] << std::endl;
    }
}

void SplitApplyCombine::endAndJoin(const uint8_t & workers_cant,
                                   std::vector<std::thread> & threads_vector,
                                   ToDoQueue & queue){
    for (uint8_t i = 0; i < workers_cant; i++)
        queue.push(ToDoToken());

    for (uint8_t i = 0; i < workers_cant; i++)
        threads_vector[i].join();
}


void SplitApplyCombine::loadAndValidate(const char * const dataset_filename,
                     const std::string & text_columns,
                     const std::string & text_workers,
                     uint32_t & columns, uint8_t & workers) {
    try {
        data_loader.openFile(dataset_filename);
    }
    catch(std::exception & e) {
        std::string msg = e.what();
        throw std::invalid_argument("Error al abrir el archivo: " + msg);
    }

    try {
        if (text_columns.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        columns = std::stoul(text_columns);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("Error al leer las columnas: " + msg);
    }

    try {
        if (text_workers.find('-') != std::string::npos)
            throw std::invalid_argument("numero negativo");
        workers = std::stoul(text_columns);
    }
    catch(std::exception& e){
        std::string msg = e.what();
        throw std::invalid_argument("Error al leer la fila inicial: " + msg);
    }
}
