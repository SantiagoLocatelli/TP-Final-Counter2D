#ifndef _LOBBY_MANAGER_H_
#define _LOBBY_MANAGER_H_

#include "../common_src/Thread.h"
#include "../common_src/Socket.h"
#include "../common_src/Protocol.h"
#include "GameList.h"

class LobbyManager: public Thread{
    private:
        GameList &gameList;
        Protocol protocol;
        bool keepReceiving;
        void run();
    
    public:
        LobbyManager(Socket skt, GameList &gameList);
        bool finished();
};

#endif
