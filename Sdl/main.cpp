#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <list>
#include "../Sdl/sdl_texture.h"
#include "draggable.h"
int main(int argc, char* argv[]){
    // variables
     
    bool quit = false;
    SDL_Event e;

    SdlWindow window("Editor", 640, 480);
    SdlRenderer renderer(&window);
    
    Draggable draggableTexture(renderer, "../Sdl/img/dot.bmp", 100, 100);
    // handle events
     
    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }else{
                draggableTexture.handleEvent(&e);
            }
        }
         //Clear screen
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        //Render background
        draggableTexture.render();

        //Update screen
        renderer.updateScreen();
    }

    return 0;
}