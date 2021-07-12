#include "ModelQueue.h"

void ModelQueue::push(std::shared_ptr<CompleteModelInfo> model){
    std::unique_lock<std::mutex> lock(m);
    queue.push(model);
    cv.notify_all();
}

std::shared_ptr<CompleteModelInfo> ModelQueue::pop(){
    std::unique_lock<std::mutex> lock(m);
    while (queue.empty()){
        cv.wait(lock);
    }

    std::shared_ptr<CompleteModelInfo> model = queue.front();
    queue.pop();

    return model;
}