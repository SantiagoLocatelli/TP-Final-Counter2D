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
        bool joined_game = false; 
        menu->run(joined_game);
        delete menu;

        if (!joined_game) return 0;

        Size windowSize {500, 500};

        MapInfo map;
        server.recv_map_info(map);

        ModelInfo model;
        server.recv_model_info(model);

        LevelInfo level;
        GameManager gameManager;
        
        gameManager.initializeLevel(level, map, model);
        GameViewer gameViewer(windowSize, level); 

        bool gameEnded = model.game_ended;
        EventManager eventManager(server, gameEnded, gameViewer);
        eventManager.start();
        Stopwatch stopwatch;

        while (joined_game && !model.game_ended) {
            stopwatch.start();
            server.recv_model_info(model);
            gameManager.updatedLevel(level, model);
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
