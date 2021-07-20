#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../LevelInfo.h"
#include "SDL2/SDL.h"

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