#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../client_src/Character/stencil.h"
#include "../client_src/Character/camera.h"
#include "../client_src/Character/character.h"
#include "../client_src/Character/animation.h"
#include "../common_src/MapInfo.h"
#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"
#include "GameManager.h"



int main(int argc, char* argv[]){

    Protocol server(Socket("localhost", argv[1], false));
    int window_w = 400, window_h = 400;
    MapInfo map;
    LevelInfo level;
    ModelInfo model;
    
    server.recv_map_info(map);

    SdlWindow window("Bocaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);

    SdlTexture pjTexture(renderer, "../common_src/img/players/ct1.bmp", 0xFF, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    SdlTexture stencilTexture(renderer, "../common_src/img/stencil.bmp");
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");


    Stencil stencil(stencilTexture, window_w, window_h);

    server.recv_model_info(model);

    GameManager game(map, model, window_w, window_h);

    
    SDL_Event e;
    bool quit = false;
    EventManager eventManager(server, quit, game);
    eventManager.start();
    Stopwatch stopwatch;

    while (!quit) {
        stopwatch.start();
        if (stopwatch.msPassed() < 33) {

            server.recv_model_info(model);
            
            renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
            renderer.clear();


            // le mandas mecha
            renderer.updateScreen();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }


    eventManager.join();
	return 0;
}


