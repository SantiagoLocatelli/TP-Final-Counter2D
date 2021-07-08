#ifndef _GAME_THREAD_H_
#define _GAME_THREAD_H_

#include "../common_src/Thread.h"
#include "GameProxy.h"
#include "ClientManager.h"
#include "EventHandler.h"
#include "Emitter.h"
#include "EventQueue.h"
#include <list>
#include <string>

class GameThread: public Thread{
    private:
        GameProxy game;
        std::list<ClientManager*> clients;
        Emitter emitter;
        EventQueue queue;
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
