#ifndef _CLIENT_MANAGER_H_
#define _CLIENT_MANAGER_H_

#include "../common/Thread.h"
#include "../common/Protocol.h"
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
        explicit ClientManager(Socket skt, EventQueue &queue, Emitter &emitter, int id);
        bool finished();

        virtual ~ClientManager() = default;
};

#endif
