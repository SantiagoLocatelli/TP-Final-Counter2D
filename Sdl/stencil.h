#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "sdl_texture.h"

class Stencil {
private:
    SdlTexture& stencil;
    SDL_Rect rect;
    double degrees = 0;

    int oldPosX;
    int oldPosY;

    int level_w;
    int level_h;
public:
    Stencil(SdlTexture& stencil, int w, int h, int level_w,int level_h);
    void centerStencil(SDL_Rect character);
    void render(int camX, int camY);
    void handleEvent(SDL_Event e);
};

#endif
