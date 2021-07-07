#ifndef _LOBBY_MANAGER_H_
#define _LOBBY_MANAGER_H_

#include "../common_src/Thread.h"
#include "GameList.h"

class LobbyManager: public Thread{
    private:
        GameList gameList;
        void run();
    
    public:
        explicit LobbyManager(Socket skt);
        bool finished();
};

#endif
