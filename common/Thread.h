#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>

class Thread {
    private:
        std::thread thread;
        virtual void run() = 0;  
 
    public:
        Thread() = default;
        
        void start();
        void join();

        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
};

#endif
