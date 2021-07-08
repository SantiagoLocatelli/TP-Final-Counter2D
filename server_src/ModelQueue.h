#ifndef _MODEL_QUEUE_H_
#define _MODEL_QUEUE_H_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include "CompleteModelInfo.h"

class ModelQueue{
    private:
        std::mutex m;
        std::condition_variable cv;
        std::queue<std::shared_ptr<CompleteModelInfo>> queue;

    public:
        void push(std::shared_ptr<CompleteModelInfo> model);
        std::shared_ptr<CompleteModelInfo> pop();
};

#endif
