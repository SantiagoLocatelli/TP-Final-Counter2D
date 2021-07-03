#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__

#include "SDL2/SDL.h"
#include "../../common_src/Sdl/sdl_texture.h"

class CrossHair {
private:
    SDL_Rect area;
    SdlTexture texture;
    int actualFrame;
    // SDL_Cursor* cursor;

public:
    CrossHair(int width, int height, SdlTexture texture);
    void setPosition(int posX, int posY);
    void render();
};

#endif