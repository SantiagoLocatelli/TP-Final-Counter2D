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

#define PIXELS_PER_METER 50


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
        boxTexture.render(it->x, it->y, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

int main(int argc, char* argv[]){

    Client server("localhost", "8080");
    int window_w = 640, window_h = 480;
    MapInfo map;
    server.recvMapInfo(map);
    LevelInfo level;
    level.width = map.length*PIXELS_PER_METER;
    level.height = map.height*PIXELS_PER_METER;
    level.w_meters = map.length;
    level.h_meters = map.height;

    SdlWindow window("Bocaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);
    SdlTexture pjTexture(renderer, "../Resources/img/dot.bmp", 0x0, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../Resources/img/bg.png");
    SdlTexture stencilTexture(renderer, "../Resources/img/stencil.png");
    SdlTexture boxTexture(renderer, "../Resources/img/green_create.bmp");

    bool quit = false;

    Stencil stencil(stencilTexture, window_w, window_h);
    Camera cam(window_w, window_h);
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
        
        // limpia el render
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        // renderizamos tuti
        renderBoxes(map.boxes, boxTexture);
        bg.render();
        pj.render();

        // le mandas mecha
        renderer.updateScreen();
    }
    return 0;
}