#include "GameList.h"
#include "../../common_src/GeneralException.h"

void GameList::createGame(GameInfo gameInfo){
    const std::lock_guard<std::mutex> lock(m);

    std::map<std::string, std::unique_ptr<GameThread>>::iterator it = gameList.find(gameInfo.name);
    if(it != gameList.end()){
        throw GeneralException("Ya existe una partida con ese nombre");
    }

    std::string path = "../../common_src/maps/";
    path += gameInfo.map;
    path += ".yaml";
    gameList[gameInfo.name] = std::unique_ptr<GameThread>(new GameThread(path));
    gameInfo.players = 0;
    gameInfoList[gameInfo.name] = gameInfo;
}

void GameList::joinGame(std::string name, Protocol protocol){
    const std::lock_guard<std::mutex> lock(m);

    std::map<std::string, std::unique_ptr<GameThread>>::iterator it = gameList.find(name);
    if (it == gameList.end()){
        throw GeneralException("No existe una partida con ese nombre");
    }

    if (gameInfoList.at(name).players == gameInfoList.at(name).max_players){
        throw GeneralException("La partida está llena");
    }

    gameInfoList.at(name).players++;
    gameList.at(name)->addPlayer(std::move(protocol));
    if (gameInfoList.at(name).players == gameInfoList[name].max_players){
        //La partida se llenó
        gameList.at(name)->start();
    }
}

std::list<GameInfo> GameList::getAvaliableGames(){
    const std::lock_guard<std::mutex> lock(m);

    std::list<std::string> gamesToDelete;
    for (auto &pair: gameList){
        if (pair.second->ended()){
            pair.second->join();
            gamesToDelete.push_back(pair.first);
        }
    }
    for (const std::string &g: gamesToDelete){
        gameList.erase(g);
    }

    std::list<GameInfo> list;
    for (auto &pair: gameInfoList){
        if (pair.second.players < pair.second.max_players){
            list.push_back(pair.second);
        }
    }

    return list;
}

GameList::~GameList(){
    for (auto &pair: gameList){
        pair.second->join();
    }
}
