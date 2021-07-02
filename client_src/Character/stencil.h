#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Sdl/sdl_renderer.h"

class Stencil {
private:
    SdlTexture stencil;
    SDL_Rect rect;
    float degrees = 0.0;

public:
    Stencil(SdlRenderer& renderer, int w, int h);
    void setPosition(int posX, int posY, float degrees);
    void render(int camX, int camY);

    Stencil& operator=(const Stencil&);
    Stencil(Stencil&& other);

};

#endif
