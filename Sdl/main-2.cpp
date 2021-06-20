#include "sdl_texture.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "camera.h"
#include "dot.h"
#include "stencil.h"

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main( int argc, char* args[]){

	//Start up SDL and create window
    SdlWindow gWindow("Conteiner", SCREEN_WIDTH, SCREEN_HEIGHT);
    SdlRenderer gRenderer(&gWindow);
    SdlTexture stencilTexture(gRenderer, "img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture gDotTexture(gRenderer, "img/dot.bmp",0, 0xFF, 0xFF);
    Dot dot(0, 0, gDotTexture);
    
    SdlTexture gBGTexture(gRenderer, "img/bg.png");
    
    Stencil stencil(stencilTexture, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
    double degrees = 0;

    //The dot that will be moving around on the screen

    //The camera area
    Camera cam(SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);            
    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                dot.handleEvent(e);
            } else if (e.type == SDL_MOUSEMOTION) {
                //stencil.handleEvent(e);
            }

        }

        //Move the dot
        dot.move(LEVEL_WIDTH, LEVEL_HEIGHT);

        //Center the camera over the dot SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        cam.centerCamera(dot.getRect());

        //Keep the camera in bounds
        cam.keepInBounds();


        //Clear screen
        gRenderer.setDrawColor( 0xFF, 0xFF, 0xFF, 0xFF );
        gRenderer.clear();

        //Render background
        gBGTexture.render( 0, 0, cam.getRect());

        stencil.centerStencil(dot.getRect());
        stencil.render(cam.getPosX(), cam.getPosY());
        //Render objects
        dot.render( cam.getPosX(), cam.getPosY() );

        //Update screen
        gRenderer.updateScreen();
    }

	return 0;
}