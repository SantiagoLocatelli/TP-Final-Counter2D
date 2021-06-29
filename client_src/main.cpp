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
#include "Events/eventManager.h"

#define PIXELS_PER_METER 50

void renderBoxes(std::list<Box> boxes, SdlTexture& boxTexture) {
    for(auto it = boxes.begin(); it != boxes.end(); it++){
        boxTexture.render(it->x, it->y, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

int main(int argc, char* argv[]){

    //Protocol server(Socket("localhost", argv[1], false));
    int window_w = 640, window_h = 480;
    MapInfo map;
    LevelInfo level;
    
    // server.recv_map_info(map);
    // level.width = map.length*PIXELS_PER_METER;
    // level.height = map.height*PIXELS_PER_METER;
    // level.w_meters = map.length;
    // level.h_meters = map.height;
    
    level.height = 768;
    level.width = 1366;
    level.w_meters = 5;
    level.h_meters = 5;

    SdlWindow window("Bocaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);
    SdlTexture pjTexture(renderer, "../common_src/img/dot.bmp", 0x0, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    SdlTexture stencilTexture(renderer, "../common_src/img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");

    bool quit = false;

    SdlTexture stencilTexture_2(renderer, "gato");
    Stencil stencil(stencilTexture_2, level.width, level.height);
    //stencil.fillStencil();


    Camera cam(window_w, window_h);
    SDL_Rect area = {0, 0, PIXELS_PER_METER, PIXELS_PER_METER};
    Cursor cursor(window_w, window_h);
    Character pj(area, pjTexture, cam, stencil, cursor);

    Background bg(backg, cam, level.width, level.height);
    
    SDL_Event e;
    ModelInfo model;
    // EventManeger eventManager(server);
    // eventManager.start();
    while (!quit) {


        //server.recvModelInfo(model);
        
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