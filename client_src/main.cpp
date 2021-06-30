#include "../Sdl/sdl_renderer.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_texture.h"
#include "../client_src/Character/stencil.h"
#include "../client_src/Character/camera.h"
#include "../client_src/Character/character.h"
#include "../client_src/Character/animation.h"
#include "../common/MapInfo.h"
#include "../Sdl/background.h"
#include "Events/eventManager.h"

#define PIXELS_PER_METER 100

void renderBoxes(std::list<Box> boxes, SdlTexture& boxTexture) {
    for(auto it = boxes.begin(); it != boxes.end(); it++){
        boxTexture.render(it->x*PIXELS_PER_METER, it->y*PIXELS_PER_METER, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

int main(int argc, char* argv[]){

    //Protocol server(Socket("localhost", argv[1], false));
    int window_w = 450, window_h = 450;
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

    SdlTexture pjTexture(renderer, "../common_src/img/players/ct1.bmp", 0xFF, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    SdlTexture stencilTexture(renderer, "../common_src/img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");

    bool quit = false;

    // SdlTexture stencilTexture_2(renderer, "gato");
    Stencil stencil(stencilTexture, level.width, level.height);
    //stencil.fillStencil();


    Camera cam(window_w, window_h);
    SDL_Rect area = {0, 0, PIXELS_PER_METER, PIXELS_PER_METER};
    Character pj(area, pjTexture, cam, stencil);

    Background bg(backg, cam, level.width, level.height);
    
    // SDL_Event e;
    // ModelInfo model;
    // // EventManeger eventManager(server);
    // // eventManager.start();
    // while (!quit) {


    //     //server.recvModelInfo(model);
        
    //     // limpia el render
    //     renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    //     renderer.clear();

    //     // renderizamos tuti
    //     renderBoxes(map.boxes, boxTexture);
    //     bg.render();
    //     pj.render();

    //     // le mandas mecha
    //     renderer.updateScreen();
    // }




    SDL_Event e;
    EventManager eventManager;
    while( !quit ){
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            switch (e.type) {
                case SDL_QUIT:
                    quit = true; 
                    break;
                default:
                    eventManager.handleEvent(pj, e);

            }
            // std::chrono::seconds secs(FRAME_RATE);
            // std::this_thread::sleep_for (std::chrono::seconds(FRAME_RATE));
            // usleep(FRAME_RATE);
        }

        //Move the dot
        // pj.update(level.width, level.height);

        //Clear screen
        renderer.setDrawColor( 0xFF, 0xFF, 0xFF, 0xFF );
        renderer.clear();

        //Render background
        bg.render();
        
        //Render objects

        // pj.render();

        //Update screen
        renderer.updateScreen();
    }

	return 0;
}


