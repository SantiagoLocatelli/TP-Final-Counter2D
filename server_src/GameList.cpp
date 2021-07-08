#include "GameList.h"

void GameList::createGame(GameInfo gameInfo){
    //TODO: Chequear que no se puedan crear partidas con el mismo nombre
    const std::lock_guard<std::mutex> lock(m);
    gameList[gameInfo.name] = std::pair<GameThread*, int>(new GameThread(gameInfo.map), 0);
    gameInfoList[gameInfo.name] = gameInfo;
}

void GameList::joinGame(std::string name, Protocol protocol){
    //TODO: Chequear que no se pueda unirse a partidas que no existan
    //TODO: Joinear los GameThread que terminaron
    const std::lock_guard<std::mutex> lock(m);
    gameList.at(name).second++;
    gameList.at(name).first->addPlayer(std::move(protocol));
    if (gameList.at(name).second == gameInfoList[name].players){
        //La partida se llenó
        gameList.at(name).first->start();
    }
}

std::list<GameInfo> GameList::getList(){
    std::list<GameInfo> list;
    for (auto pair: gameInfoList){
        list.push_back(pair.second);
    }

    return list;
}
