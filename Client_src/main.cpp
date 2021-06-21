#include "client.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include "sdl_texture.h"
#include "stencil.h"
#include "dot.h"
#include "camera.h"

int main(int argc, char* argv[]){

    Client server("localhost", "8080");
    int window_w, window_h;
    server.recvWindowSize(window_w, window_h);


    SdlWindow window("BOcaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);
    SdlTexture dotTexture(renderer, "../Sdl/img/dot.bmp", 0x0, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../Sdl/img/bg.png");
    SdlTexture stencilTexture(renderer, "../Sdl/img/stencil.png");

    bool quit = false;

    //Stencil stencil(stencilTexture, window_w, window_h);
    Camera cam(window_w, window_h);
    //Dot dot(0, 0, dotTexture, cam, stencil);

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0){
            switch (e.type) {
                case SDL_QUIT:
                    quit = true; break;
            }
        }
        int dotX, dotY;
        server.recvPosition(dotX, dotY);
        
        SDL_Rect dotRect = {dotX, dotY, dotTexture.getWidth(), dotTexture.getHeight()};
        //centra la camara en el personaje
        cam.centerCamera(dotRect);
        // mantiene la camara en los limites del background
        cam.keepInBounds(backg.getWidth(), backg.getHeight());

        // limpia el render
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        // renderizamos tuti
        dotTexture.render(dotX, dotY);
        backg.render(dotX, dotY, cam.getRect());

        // le mandas mecha
        renderer.updateScreen();
    }
    return 0;
}