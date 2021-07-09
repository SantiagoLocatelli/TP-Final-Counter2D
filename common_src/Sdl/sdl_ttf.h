#ifndef __SDL_TTF_H__
#define __SDL_TTF_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_renderer.h"
#include "sdl_texture.h"
#include <string>

struct Color {
    uint8_t r,g,b;
};

class SdlTtf{
private:
    SdlRenderer& renderer;
    TTF_Font* font;

public:

    SdlTtf(SdlRenderer& renderer, std::string path, int size = 25);
    ~SdlTtf();

    SdlTexture createTextureFromText(std::string text, struct Color color);
};

#endif