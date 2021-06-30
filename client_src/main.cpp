#include "client.h"
#include "../Sdl/sdl_renderer.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_texture.h"
#include "../client_src/Character/stencil.h"
#include "../client_src/Character/camera.h"
#include "../client_src/Character/character.h"
#include "../client_src/Character/animation.h"
#include "../client_src/Character/cursor.h"
#include "../common/MapInfo.h"
#include "../Sdl/background.h"

#define PIXELS_PER_METER 100


// struct Box{
//     int x;
//     int y;
// };

// struct MapInfo{
//     int height;
//     int length;
//     std::list<Box> boxes;
// };


void renderBoxes(std::list<Box> boxes, SdlTexture& boxTexture) {
    for(auto it = boxes.begin(); it != boxes.end(); it++){
        boxTexture.render(it->x*PIXELS_PER_METER, it->y*PIXELS_PER_METER, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

int main(int argc, char* argv[]){

    Client server("localhost", argv[1]);
    int window_w = 400, window_h = 400;
    MapInfo map;
    server.recvMapInfo(map);
    LevelInfo level;
    level.width = map.length*PIXELS_PER_METER;
    level.height = map.height*PIXELS_PER_METER;
    level.w_meters = map.length;
    level.h_meters = map.height;

    SdlWindow window("Bocaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);
    SdlTexture pjTexture(renderer, "../common_src/img/ct1.bmp", 0xFF, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    SdlTexture stencilTexture(renderer, "../common_src/img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");

    bool quit = false;

    Stencil stencil(stencilTexture, window_w, window_h);
    Camera cam(level.width, level.height);
    SDL_Rect area = {0, 0, PIXELS_PER_METER, PIXELS_PER_METER};
    Cursor cursor(window_w, window_h);
    Character pj(area, pjTexture, cam, stencil, cursor);

    Background bg(backg, cam, level.width, level.height);
    
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0){
            switch (e.type) {
                case SDL_QUIT:
                    quit = true; break;
                case SDL_KEYDOWN:
                    server.sendEvent(e); break;
                case SDL_KEYUP:
                    server.sendEvent(e); break;
            }
        }
        ModelInfo model;
        server.recvModelInfo(model);
        pj.update(model, level);
        
        // limpia el render
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        // renderizamos tuti
        bg.render();
        renderBoxes(map.boxes, boxTexture);
        pj.render();

        // le mandas mecha
        renderer.updateScreen();
    }
    return 0;
}