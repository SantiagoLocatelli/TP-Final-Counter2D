#include "Emitter.h"

void Emitter::emitMap(MapInfo map){
    const std::lock_guard<std::mutex> lock(m);

    this->map = map;
    notified = !notified;
    cv.notify_all();
}

void Emitter::emitModel(CompleteModelInfo model){
    const std::lock_guard<std::mutex> lock(m);

    this->model = model;
    notified = !notified;
    cv.notify_all();
}

MapInfo& Emitter::recvMap(){
    std::unique_lock<std::mutex> lock(m);
    bool old_notified = notified;
    while (old_notified == notified){
        cv.wait(lock);
    }

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
