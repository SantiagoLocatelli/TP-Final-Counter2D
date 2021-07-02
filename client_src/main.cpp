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

    GameManager game(map, model, window_w, window_h);

    SDL_Event e;
    bool quit = false;
    EventManager eventManager(server, quit, game);
    eventManager.start();
    Stopwatch stopwatch;

    while (!quit /*|| !model.game_ended*/) {
        stopwatch.start();
        if (stopwatch.msPassed() < 33) {

            server.recv_model_info(model);
            game.update(model);
            game.render();

            // le mandas mecha
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    eventManager.join();
	return 0;
}


