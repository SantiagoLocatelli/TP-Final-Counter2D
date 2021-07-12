#ifndef _ACCEPTER_H_
#define _ACCEPTER_H_

#include "../../common_src/Thread.h"
#include "../../common_src/Socket.h"
#include "LobbyManager.h"
#include "../game_management/GameList.h"
#include <list>

class Accepter : public Thread{
    private:
        Socket skt;
        GameList &gameList;
        std::list<LobbyManager*> clientList;

        void run() override;

    public:
        explicit Accepter(char const *port, GameList &gameList);

        void stop();
};

#endif
