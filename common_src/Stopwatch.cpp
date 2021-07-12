#include "Stopwatch.h"

void Stopwatch::start(){
    start_time = std::chrono::high_resolution_clock::now();
}

size_t Stopwatch::msPassed(){
    //TODO: Cambiar para que devuelva un float con los segundos que pasaron
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
    end_time - start_time);

    return time.count();
}
