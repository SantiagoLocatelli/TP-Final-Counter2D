#include "sdl_texture.h"
#include "sdl_window.h"
#include "sdl_renderer.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "camera.h"
#include "character.h"
#include "stencil.h"
#include "event_manager.h"
#include "background.h"
#include <iostream>
#include <unistd.h>

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


void saveTexture(SdlRenderer& ren, SdlTexture& tex, const char *filename, int w, int h){
    SDL_Surface *surf;
    int st;
    void *pixels;
    int format  = SDL_PIXELFORMAT_RGBA32;
    pixels  = NULL;
    surf    = NULL;
    SDL_Texture* target = ren.getRenderTarget();

    SDL_Texture* ren_tex;
    ren_tex = ren.createTexture(w, h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we 
     * can access
     */
    st = ren.setRenderTarget(ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
    }

    ren.setDrawColor(0x00, 0x00, 0x00, 0x00);
    ren.clear();

    st = tex.renderCopy();
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        SDL_FreeSurface(surf);
    }

    st = ren.renderReadPixels(pixels, w, format);
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        return;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        return;
    }

    ren.setRenderTarget(target);
    /* Save result to an image */
    st = SDL_SaveBMP(surf, filename);
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        SDL_DestroyTexture(ren_tex);
        return;
    }
}

int main( int argc, char* args[]){

	//Start up SDL and create window
    SdlWindow gWindow("Conteiner", SCREEN_WIDTH, SCREEN_HEIGHT);
    SdlRenderer gRenderer(&gWindow);
    SdlTexture stencilTexture(gRenderer, "img/stencil.png", 0xFF, 0xFF, 0xFF);
    SdlTexture gDotTexture(gRenderer, "img/ct1.bmp", 0x00, 0x00, 0x00);
    
    SdlTexture gBGTexture(gRenderer, "img/bg.png");
    Camera cam(SCREEN_WIDTH, SCREEN_HEIGHT);
    Background bg(gBGTexture, cam);
    
    Stencil stencil(stencilTexture, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Rect area = {0, 0, 50, 50};            
    Character pj(area, gDotTexture, cam, stencil);
    
    
    // saveTexture(gRenderer, stencilTexture, "img/image.bmp", LEVEL_WIDTH, LEVEL_HEIGHT);
    // SdlTexture stencilTexture_2(gRenderer, "img/image.bmp");
    //The camera area

    bool quit = false;
    SDL_Event e;
    SDL_Event last_e;
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
            last_e = e;
            // std::chrono::seconds secs(FRAME_RATE);
            // std::this_thread::sleep_for (std::chrono::seconds(FRAME_RATE));
            // usleep(FRAME_RATE);
        }

        //Move the dot
        pj.update(LEVEL_WIDTH, LEVEL_HEIGHT);

        //Clear screen
        gRenderer.setDrawColor( 0xFF, 0xFF, 0xFF, 0xFF );
        gRenderer.clear();

        //Render background
        bg.render();
        
        //Render objects
        pj.render();

        //Update screen
        gRenderer.updateScreen();
    }

	return 0;
}