#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "../../common_src/Sdl/sdl_texture.h"

class Stencil {
private:
    SdlTexture& stencil;
    SDL_Rect rect;
    float degrees = 0.0;

public:
    Stencil(SdlTexture& stencil, int w, int h);
    void setStencil(SDL_Rect character, float degrees);
    void render(int camX, int camY);

    Stencil& operator=(const Stencil&);
    Stencil(Stencil&& other);

};

#endif
