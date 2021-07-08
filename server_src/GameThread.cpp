#include "GameThread.h"
#include <utility>
#include "../common_src/Stopwatch.h"

#include <iostream>
#include <chrono>

GameThread::GameThread(std::string map_path):game(map_path), eventHandler(game), gameEnded(false), playerNumber(0){}

void GameThread::addPlayer(Protocol protocol){
    clients.push_back(new ClientManager(std::move(protocol), queue, emitter, playerNumber));
    playerNumber++;
    game.createPlayer();
}

bool GameThread::ended(){
    return gameEnded;
}

void GameThread::run(){
    for (auto cli: clients){
        cli->start();
    }
    try{
        
        Stopwatch stopwatch;

        emitter.emitMap(game.getMapInfo());

        do{
            stopwatch.start();
            while (stopwatch.msPassed() < 33){
                //TODO: Sacar este busy wait
                if (!queue.isEmpty()){
                    int id;
                    Event event = queue.pop(id);
                    eventHandler.executeEvent(event, id);
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }

            game.step();
            emitter.emitModel(std::move(game.getModelInfo()));
            game.clearFrameEvents();
        } while (!game.ended());
    } catch (const std::exception &e){
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    
    gameEnded = true;
    for (ClientManager *cli: clients){
        cli->join();
        delete cli;
    }
}
