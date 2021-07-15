#include "GameThread.h"
#include <utility>
#include "../../common_src/Stopwatch.h"

#include <iostream>
#include <chrono>
#include <memory>

GameThread::GameThread(std::string map_path):game(map_path, gameConfig), eventHandler(game), gameEnded(false), playerNumber(0){}

void GameThread::addPlayer(Protocol protocol){
    const std::lock_guard<std::mutex> lock(m);
    modelQueues.emplace_back();
    clients.push_back(std::unique_ptr<ClientManager>(new ClientManager(std::move(protocol), eventQueue, modelQueues.back(), game.getMapInfo(), playerNumber)));
    if (playerNumber%2 == 0){
        game.createPlayer(TERROR);
    } else {
        game.createPlayer(COUNTER);
    }
    playerNumber++;
}

bool GameThread::ended(){
    return gameEnded;
}

void GameThread::run(){
    for (std::unique_ptr<ClientManager> &cli: clients){
        cli->start();
    }

    game.setUpGame();
    auto model = std::make_shared<CompleteModelInfo>(std::move(game.getModelInfo()));
    for (ModelQueue &queue : modelQueues){
        queue.push(model);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2)); 


    try{
        
        Stopwatch stopwatch;
        do{
            stopwatch.start();
            while (stopwatch.msPassed() < FRAME_MS){
                if (!eventQueue.isEmpty()){
                    int id;
                    Event event = eventQueue.pop(id);
                    eventHandler.executeEvent(event, id);
                } else {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }

            game.step((float)FRAME_MS/(float)1000);
            auto model = std::make_shared<CompleteModelInfo>(std::move(game.getModelInfo()));
            for (ModelQueue &queue : modelQueues){
                queue.push(model);
            }
            game.clearFrameEvents();
        } while (!game.ended());
    } catch (const std::exception &e){
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    
    gameEnded = true;
    for (std::unique_ptr<ClientManager> &cli: clients){
        cli->join();
    }
}
