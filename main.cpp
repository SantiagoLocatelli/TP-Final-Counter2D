#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <list>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_window.h"
#include "../Sdl/sdl_renderer.h"
#include "../Sdl/draggable.h"
#include "../Sdl/game_object.h"
#include "../Sdl/floor.h"
int main(int argc, char* args[]){

    SdlWindow window("Map", 640, 480);
    SdlWindow windowTexture("Textures", 640, 480);
    SdlRenderer renderer(&window);
    SdlRenderer rendererTextures(&windowTexture);

    SdlTexture dust(rendererTextures, "dust.png");
    SdlTexture grass(rendererTextures, "gras1.jpg");

    Draggable draggableTexture(rendererTextures, "dust.png", 0, 0);

    Floor floor;

    GameObject object(100, 100, floor,renderer, "dust.png");

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while(!quit){
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }

            window.handleEvent(e);
            windowTexture.handleEvent(e);
            draggableTexture.handleEvent(&e);
        }

        if(!window.isMinimized()){
            renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
            renderer.clear();
        }

        if(!windowTexture.isMinimized()){
            rendererTextures.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
            rendererTextures.clear();
            dust.render(0,0);
            draggableTexture.render();
            grass.render(0, 64);
        }
        
        if(!window.isMinimized()){
            renderer.updateScreen();
        }

        if(!windowTexture.isMinimized()){
            rendererTextures.updateScreen();
        }
            
        //Check all windows
        if(!windowTexture.isShown()){
            if(!window.isShown()){
                quit = true;
            }
        }
    }
    return 0;
}

