#include "Stopwatch.h"

void Stopwatch::start(){
    start_time = std::chrono::high_resolution_clock::now();
}

size_t Stopwatch::msPassed(){
    std::chrono::duration<std::chrono::milliseconds> time;
    time = start_time - std::chrono::high_resolution_clock::now();

    return time.count().count();
}
