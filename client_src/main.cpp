#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"
#include <iostream>


int main(int argc, char* argv[]){
    try{
        Protocol server(Socket("localhost", argv[1], false));
        int window_w = 500, window_h = 500;

        MapInfo map;
        server.recv_map_info(map);

        ModelInfo model;
        server.recv_model_info(model);

        LevelInfo level;
        GameManager::initializeLevel(map, model, level);
        GameViewer gameViewer(window_w, window_h, level); 

        bool quit = false;
        EventManager eventManager(server, quit, gameViewer);
        eventManager.start();
        Stopwatch stopwatch;

        while (!quit && !model.game_ended) {
            stopwatch.start();
            server.recv_model_info(model);

            GameManager::updatedLevel(model, level);
            gameViewer.update(level);
            gameViewer.render();
            while (stopwatch.msPassed() < 33) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        eventManager.stop();
        eventManager.join();
    } catch (const std::exception &e){
        std::cerr << "ERROR:" << e.what() << std::endl;
    }
    return 0;
}
