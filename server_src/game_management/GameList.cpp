#include "GameList.h"

void GameList::createGame(GameInfo gameInfo){
    //TODO: Chequear que no se puedan crear partidas con el mismo nombre
    const std::lock_guard<std::mutex> lock(m);
    std::string path = "../../common_src/maps/";
    path += gameInfo.map;
    path += ".yaml";
    gameList[gameInfo.name] = std::unique_ptr<GameThread>(new GameThread(path));
    gameInfo.players = 0;
    gameInfoList[gameInfo.name] = gameInfo;
}

void GameList::joinGame(std::string name, Protocol protocol){
    //TODO: Chequear que no se pueda unirse a partidas que no existan
    //TODO: Joinear los GameThread que terminaron
    //TODO: No permitir unirse a juegos que ya empezaron
    const std::lock_guard<std::mutex> lock(m);
    gameInfoList.at(name).players++;
    gameList.at(name)->addPlayer(std::move(protocol));
    if (gameInfoList.at(name).players == gameInfoList[name].max_players){
        //La partida se llenó
        gameList.at(name)->start();
    }
}

std::list<GameInfo> GameList::getList(){
    const std::lock_guard<std::mutex> lock(m);
    std::list<GameInfo> list;
    for (auto pair: gameInfoList){
        list.push_back(pair.second);
    }

    return list;
}

GameList::~GameList(){
    for (auto &pair: gameList){
        pair.second->join();
    }
}
