#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/MapInfo.h"
#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"



int main(int argc, char* argv[]){

    Protocol server(Socket("localhost", argv[1], false));
    int window_w = 400, window_h = 400;
    MapInfo map;
    ModelInfo model;

    server.recv_map_info(map);

    // SdlTexture pjTexture(renderer, "../common_src/img/players/ct1.bmp", 0xFF, 0xFF, 0xFF);
    // SdlTexture backg(renderer, "../common_src/img/bg.png");
    // SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");


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
            //game.update(model);
            //game.render();

            // le mandas mecha
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }


    eventManager.join();
	return 0;
}


