#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"


int main(int argc, char* argv[]){

    Protocol server(Socket("localhost", argv[1], false));
    int window_w = 400, window_h = 400;

    MapInfo map;
    server.recv_map_info(map);

    ModelInfo model;
    server.recv_model_info(model);

    GameManager gameManager(map);
    GameViewer gameViewer(window_w, window_h, gameManager.updatedLevel(model)); 

    bool quit = false;
    EventManager eventManager(server, quit, gameViewer);
    eventManager.start();
    Stopwatch stopwatch;

    while (!quit && !model.game_ended) {
        stopwatch.start();
        server.recv_model_info(model);
        
        gameViewer.update(gameManager.updatedLevel(model));
        gameViewer.render();
        while (stopwatch.msPassed() < 33) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    
    eventManager.stop();
    eventManager.join();
	return 0;
}
