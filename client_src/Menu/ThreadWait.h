#ifndef __THREAD_WAIT_H__
#define __THREAD_WAIT_H__

#include "../../common_src/Protocol.h"
#include "../common_src/Thread.h"

class ThreadWait: public Thread {
private:
    Protocol& protocol;
    bool& loading;
    MapInfo& map;
    ModelInfo& model;

public:

    ThreadWait(Protocol& protocol, bool& loading, MapInfo& map, ModelInfo& model);
    ~ThreadWait() = default;
    
    void run() override;

    ThreadWait& operator=(const ThreadWait&) = delete;
    ThreadWait(const ThreadWait&) = delete;
    ThreadWait& operator=(ThreadWait&& other) = delete;
};

#endif