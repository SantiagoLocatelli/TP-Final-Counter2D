#include "LobbyManager.h"
#include "../common_src/GeneralException.h"
#include <iostream>
#include <utility>

LobbyManager::LobbyManager(Socket skt, GameList &gameList):protocol(std::move(skt)), gameList(gameList), keepReceiving(true){}

void LobbyManager::run(){
    try{
        while (keepReceiving){
            Event event;
            protocol.recv_event(event);
            switch (event.type){
            case CREATE_GAME:
                gameList.createGame(event.info.gameInfo);
                gameList.joinGame(event.info.gameInfo.name, std::move(protocol));
                keepReceiving = false;
                break;
            case JOIN_GAME:
                gameList.joinGame(event.info.gameInfo.name, std::move(protocol));
                keepReceiving = false;
                break;
            case LIST_GAMES:
                std::list<GameInfo> &list = gameList.getList();
                protocol.send_game_list(list);
                break;
            
            default:
                throw GeneralException("Se recibió un evento inesperado\n");
                break;
            }
        }
    } catch(const std::exception& e){
        std::cout << "ERROR en `LobbyManager`: " << e.what() << std::endl;
        protocol.close();
    }
}