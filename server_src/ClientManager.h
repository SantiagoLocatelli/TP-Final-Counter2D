#ifndef _CLIENT_MANAGER_H_
#define _CLIENT_MANAGER_H_

#include "../common_src/Thread.h"
#include "../common_src/Protocol.h"
#include "EventQueue.h"
#include "Emitter.h"
#include "EventReceiver.h"

class ClientManager: public Thread{
    private:
        Protocol protocol;
        Emitter &emitter;
        int id;
        EventReceiver receiver;
        bool keep_sending;

        void run() override;
        
    public:
        ClientManager(Protocol protocol, EventQueue &queue, Emitter &emitter, int id);
        bool finished();

        virtual ~ClientManager() = default;
};

#endif
