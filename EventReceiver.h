#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <thread>
#include "GameManager.h"
#include "protocol/Protocol.h"

class EventReceiver{
    private:
        std::thread thread;
        GameManager &game;
        bool keep_listening;
        Protocol &protocol;

        void run();
    public:
        explicit EventReceiver(GameManager &game, Protocol &protocol);

        void start();
        void stop();
        void join();
};

#endif
