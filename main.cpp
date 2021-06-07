#include "sdl_texture.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include "sdl_mixer.h"
#include <stdio.h>
#include <string>
#include <vector>

int main(int argc, char argv[]){
    SdlWindow window("Counter", 640, 480);
    SdlRenderer renderer(&window);
    std::vector<std::string> chunks = {"sound/letsgo.mp3", "sound/gogogo.mp3"};
    SdlMixer music("sound/resident.mp3", chunks);
    SdlTexture backgroundTexture(renderer, "img/counter.jpeg");
    SdlTexture stencilTexture(renderer, "img/stencil.png");
    stencilTexture.setBlendMode(SDL_BLENDMODE_BLEND);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
    Uint8 a = 150;
    double degrees = 0;

    //While application is running
    while (!quit){
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
        //gArrowTexture.render( ( SCREEN_WIDTH - gArrowTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gArrowTexture.getHeight() ) / 2, NULL, degrees, NULL, flipType );
        stencilTexture.render((window.getWidth()/2) - 500, (window.getHeight()/2) - 500, 1000, 1000, NULL, degrees);

        //Update screen
        renderer.updateScreen();
    }
    return 0;
}