#ifndef _ACCEPTER_H_
#define _ACCEPTER_H_

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "EventQueue.h"
#include "Emitter.h"
#include "ClientManager.h"

#include <list>

class Accepter : public Thread{
    private:
        Socket skt;
        EventQueue &queue;
        Emitter &emitter;
        std::list<ClientManager*> clientList;

        void run() override;

    public:
        explicit Accepter(char const *port
        , EventQueue &queue, Emitter &emitter);

        void stop();
};

#endif
