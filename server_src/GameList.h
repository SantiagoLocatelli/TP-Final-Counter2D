#ifndef _GAME_LIST_H_
#define _GAME_LIST_H_

#include "GameProxy.h"
#include "../common_src/GameInfo.h"
#include "../common_src/Protocol.h"
#include "GameThread.h"
#include <mutex>
#include <map>
#include <list>
#include <string>
#include <utility>

class GameList{
    private:
        std::map<std::string, GameInfo> gameInfoList;
        std::map<std::string, GameThread*> gameList;
        std::mutex m;
    
    public:
        void createGame(GameInfo gameInfo);
        void joinGame(std::string name, Protocol protocol);
        std::list<GameInfo> getList();
};

#endif
