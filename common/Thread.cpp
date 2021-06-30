#include "Thread.h"
#include <utility>

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread &&other) {
    thread = std::move(other.thread);
}

Thread &Thread::operator=(Thread &&other) {
    if (this == &other){
        return *this;
    }

    thread = std::move(other.thread);
    return *this;
}
