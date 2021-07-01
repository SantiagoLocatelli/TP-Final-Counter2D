#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../client_src/Character/stencil.h"
#include "../client_src/Character/camera.h"
#include "../client_src/Character/character.h"
#include "../client_src/Character/animation.h"
#include "../common_src/MapInfo.h"
#include "../common_src/Sdl/background.h"
#include "Events/eventManager.h"
#include "../common_src/Stopwatch.h"

#define PIXELS_PER_METER 100

void renderBoxes(std::list<Box> boxes, SdlTexture& boxTexture, Camera& cam) {
    for(auto it = boxes.begin(); it != boxes.end(); it++){
        boxTexture.render(it->x*PIXELS_PER_METER - cam.getPosX(), it->y*PIXELS_PER_METER - cam.getPosY(), PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

int main(int argc, char* argv[]){

    Protocol server(Socket("localhost", argv[1], false));
    int window_w = 400, window_h = 400;
    MapInfo map;
    LevelInfo level;
    
    server.recv_map_info(map);
    level.width = map.length*PIXELS_PER_METER;
    level.height = map.height*PIXELS_PER_METER;
    level.w_meters = map.length;
    level.h_meters = map.height;
    

    SdlWindow window("Bocaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);

    SdlTexture pjTexture(renderer, "../common_src/img/players/ct1.bmp", 0xFF, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    SdlTexture stencilTexture(renderer, "../common_src/img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");


    Stencil stencil(stencilTexture, window_w, window_h);


    Camera cam(window_w, window_h);
    SDL_Rect area = {0, 0, PIXELS_PER_METER, PIXELS_PER_METER};
    Character pj(area, pjTexture, cam, stencil);

    Background bg(backg, cam, level.width, level.height);
    
    SDL_Event e;
    ModelInfo model;
    bool quit = false;
    EventManager eventManager(server, quit, pj);
    eventManager.start();
    Stopwatch stopwatch;

    while (!quit) {
        stopwatch.start();
        if (stopwatch.msPassed() < 33) {

            server.recv_model_info(model);
            pj.update(model, level);
            
            renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
            renderer.clear();

            bg.render();
            renderBoxes(map.boxes, boxTexture, cam);
            pj.render();

            // le mandas mecha
            renderer.updateScreen();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }


    eventManager.join();
	return 0;
}


