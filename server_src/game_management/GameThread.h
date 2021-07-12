#ifndef _GAME_THREAD_H_
#define _GAME_THREAD_H_

#include "../../common_src/Thread.h"
#include "GameProxy.h"
#include "../communications/ClientManager.h"
#include "EventHandler.h"
#include "../communications/ModelQueue.h"
#include "../communications/EventQueue.h"
#include <list>
#include <string>
#include <memory>
#include <mutex>

class GameThread: public Thread{
    private:
        GameConfig gameConfig;
        GameProxy game;
        std::list<std::unique_ptr<ClientManager>> clients;
        std::list<ModelQueue> modelQueues;
        EventQueue eventQueue;
        EventHandler eventHandler;
        bool gameEnded;
        int playerNumber;
        std::mutex m;

        void run();
    
    public:
        explicit GameThread(std::string map_path);
        void addPlayer(Protocol protocol);
        bool ended();
};

#endif
