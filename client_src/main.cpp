#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"
#include <iostream>


int main(int argc, char* argv[]){
    try{
        Protocol server(Socket("localhost", argv[1], false));
        int window_w = 1100, window_h = 1100;

        MapInfo map;
        server.recv_map_info(map);

        ModelInfo model;
        server.recv_model_info(model);

        GameManager game(map, model, window_w, window_h);

        bool quit = false;
        EventManager eventManager(server, quit, game);
        eventManager.start();
        Stopwatch stopwatch;

        while (!quit && !model.game_ended) {
            stopwatch.start();
            server.recv_model_info(model);
            game.update(model);
            game.render();
            while (stopwatch.msPassed() < 33) {
                // le mandas mecha
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
