#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__

#include "SDL2/SDL.h"
#include "../../common_src/Sdl/sdl_texture.h"
#include "../levelInfo.h"

class CrossHair {
private:
    SDL_Rect area;
    SdlTexture texture;

public:
    CrossHair(int width, int height, SdlTexture texture);
    void setPosition(Coordinate pos);
    void render();
};

#endif