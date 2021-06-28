#include "Emitter.h"
#include <utility>

void Emitter::emitMap(MapInfo map){
    const std::lock_guard<std::mutex> lock(m);
    this->map = map;
}

void Emitter::emitModel(CompleteModelInfo model){
    const std::lock_guard<std::mutex> lock(m);

    this->model = std::move(model);
    notified = !notified;
    cv.notify_all();
}

MapInfo& Emitter::recvMap(){
    return map;
}

CompleteModelInfo& Emitter::recvModel(){
    std::unique_lock<std::mutex> lock(m);
    bool old_notified = notified;
    while (old_notified == notified){
        cv.wait(lock);
    }

    return model;
}
