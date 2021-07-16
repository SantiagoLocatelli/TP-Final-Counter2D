#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"
#include <iostream>
#include "Menu.h"


int main(int argc, char* argv[]){
    try{
        Protocol server(Socket("localhost", argv[1], false));

        Size menuSize = {640, 480};
        Menu* menu = new Menu(menuSize, server);
        menu->run();
        delete menu;

        Size windowSize {500, 500};

        MapInfo map;
        server.recv_map_info(map);

        ModelInfo model;
        server.recv_model_info(model);

        LevelInfo level;
        GameManager gameManager;
        
        level = gameManager.initializeLevel(map, model);
        GameViewer gameViewer(windowSize, level); 

        bool quit = false;
        EventManager eventManager(server, quit, gameViewer);
        eventManager.start();
        Stopwatch stopwatch;

        while (!quit && !model.game_ended) {
            stopwatch.start();
            server.recv_model_info(model);
            level = gameManager.updatedLevel(model);
            gameViewer.update(level);
            gameViewer.render();
            while (stopwatch.msPassed() < FRAME_MS) {
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
