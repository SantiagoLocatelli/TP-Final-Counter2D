#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <chrono>

class Stopwatch{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

    public:
        void start();

        //Milisegundos desde que se llamó a start
        size_t msPassed();
};

#endif
