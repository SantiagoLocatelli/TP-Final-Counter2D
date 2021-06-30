#ifndef _EMITTER_H_
#define _EMITTER_H_

#include "CompleteModelInfo.h"
#include "../common/MapInfo.h"
#include <mutex>
#include <condition_variable>

class Emitter{
    private:
        MapInfo map;
        CompleteModelInfo model;
        std::mutex m;
        std::condition_variable cv;

        bool notified;
    
    public:
        Emitter();
        void emitMap(MapInfo map);
        void emitModel(CompleteModelInfo model);
        MapInfo& recvMap();
        CompleteModelInfo& recvModel();

        Emitter(const Emitter&) = delete;
        Emitter& operator=(const Emitter&) = delete;

};

#endif
