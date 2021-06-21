#include "client.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include "sdl_texture.h"

int main(int argc, char* argv[]){

    Client server("localhost", "8080");
    int window_w, window_h;
    server.recvWindowSize(window_w, window_h);


    SdlWindow window("BOcaaaaaa", window_w, window_h);
    SdlRenderer renderer(&window);
    SdlTexture dot(renderer, "../Sdl/img/dot.bmp", 0x0, 0xFF, 0xFF);
    SdlTexture backg(renderer, "../Sdl/img/bg.png");
    
    
    return 0;
}