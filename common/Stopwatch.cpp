#include "Stopwatch.h"

void Stopwatch::start(){
    start_time = std::chrono::high_resolution_clock::now();
}

size_t Stopwatch::msPassed(){
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
    start_time - end_time);

    return time.count();
}
