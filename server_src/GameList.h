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
#include <memory>

class GameList{
    private:
        std::map<std::string, GameInfo> gameInfoList;
        std::map<std::string, std::unique_ptr<GameThread>> gameList;
        std::mutex m;
    
    public:
        void createGame(GameInfo gameInfo);
        void joinGame(std::string name, Protocol protocol);
        std::list<GameInfo> getList();
        ~GameList();
};

#endif
