#include "sdl_texture.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include "sdl_mixer.h"
#include "button.h"
#include <stdio.h>
#include <string>
#include <vector>

void menu(SdlRenderer renderer);

int main(int argc, char argv[]){
    SdlWindow window("Counter", 640, 480);
    SdlRenderer renderer(&window);
    std::vector<std::string> chunks = {"sound/letsgo.mp3", "sound/gogogo.mp3"};
    SdlMixer music("sound/resident.mp3", chunks);
    SdlTexture backgroundTexture(renderer, "img/counter.jpeg");
    SdlTexture stencilTexture(renderer, "img/stencil.png", 0xFF, 0xFF, 0xFF);
    stencilTexture.setBlendMode(SDL_BLENDMODE_BLEND);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
    Uint8 a = 150;
    double degrees = 0;
    SdlTexture* otherTexture = NULL;
    //While application is running
    while (!quit){
        bool normalScreen = true;
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0){
            //User requests quit
            if(e.type == SDL_QUIT){
                quit = true;
            }else if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_a:
                        degrees -= 10;
                        break;
                        
                    case SDLK_d:
                        degrees += 10;
                        break;

                    case SDLK_1:
                        music.playChunk(0);
                        break;

                    case SDLK_2:
                        music.playChunk(1);
                        break;

                    case SDLK_3:
                        menu(renderer);
                        break;

                    case SDLK_8:
                        music.pause();
                        break;

                    case SDLK_9:
                        music.play();
                        break;
                }
            }
        }
        //Clear screen
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        //Render background
        backgroundTexture.render(0, 0, window.getWidth(), window.getHeight());

        //Render front blended
        stencilTexture.setAlpha(a);
        stencilTexture.render((window.getWidth()/2) - 500, (window.getHeight()/2) - 500, 1000, 1000, NULL, degrees);

        //Update screen
        renderer.updateScreen();
    }
    return 0;
}


void menu(SdlRenderer renderer){
    SdlTexture texturePlay(renderer, "img/digital-7.ttf", 26, "Play", 255, 255, 255);
    SdlTexture textureEdit(renderer, "img/digital-7.ttf", 26, "Edit map", 255, 255, 255);
    SdlTexture textureOptions(renderer, "img/digital-7.ttf", 26, "Options", 255, 255, 255);

    SdlButton button1(&texturePlay, 100, 100);
    SdlButton button2(&textureEdit, 100, 200);
    SdlButton button3(&textureOptions, 100, 300);
    
    bool quit = false;

    //Event handler
    SDL_Event e;
    //While application is running
    while (!quit){
        bool normalScreen = true;
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0){
            //User requests quit
            if(e.type == SDL_QUIT){
                quit = true;
            }else{
                button1.handleEvent(&e);
                button2.handleEvent(&e);
                button3.handleEvent(&e);
            }
        }
        renderer.setDrawColor(0, 0, 0, 0);
        renderer.clear();
        //Render buttons

        button1.render();
        button2.render();
        button3.render();

        //Update screen
        renderer.updateScreen();
    }   
}