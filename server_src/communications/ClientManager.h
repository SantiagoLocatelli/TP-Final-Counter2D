#ifndef _CLIENT_MANAGER_H_
#define _CLIENT_MANAGER_H_

#include "../../common_src/Thread.h"
#include "../../common_src/Protocol.h"
#include "EventQueue.h"
#include "EventReceiver.h"
#include "ModelQueue.h"
#include <atomic>

class ClientManager: public Thread{
    private:
        Protocol protocol;
        int id;
        EventReceiver receiver;
        std::atomic_bool keep_sending;
        ModelQueue &modelQueue;
        MapInfo map;
        std::atomic_bool ready;


        void run() override;
        
    public:
        ClientManager(Protocol protocol, EventQueue &eventQueue, ModelQueue &modelQueue, MapInfo map, int id);
        bool finished();
        bool isReady();

        virtual ~ClientManager() = default;
};

#endif
