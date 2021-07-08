#ifndef _GAME_THREAD_H_
#define _GAME_THREAD_H_

#include "../common_src/Thread.h"
#include "GameProxy.h"
#include "ClientManager.h"
#include "EventHandler.h"
#include "ModelQueue.h"
#include "EventQueue.h"
#include <list>
#include <string>
#include <memory>

class GameThread: public Thread{
    private:
        GameProxy game;
        std::list<std::unique_ptr<ClientManager>> clients;
        std::list<ModelQueue> modelQueues;
        EventQueue eventQueue;
        EventHandler eventHandler;
        bool gameEnded;
        int playerNumber;

        void run();
    
    public:
        explicit GameThread(std::string map_path);
        void addPlayer(Protocol protocol);
        bool ended();
};

#endif
