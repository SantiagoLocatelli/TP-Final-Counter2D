#ifndef __SDL_TTF_H__
#define __SDL_TTF_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_renderer.h"
#include "../../client_src/levelInfo.h"
#include <string>

class TextTexture{

private:
    SdlRenderer& renderer;
    TTF_Font* font;
    SDL_Texture* mTexture;
    Size size;
    Coordinate pos;

public:

    TextTexture(SdlRenderer& renderer, std::string path, int size = 25);
    ~TextTexture();

    void changeFontSize(int size);
    void setText(std::string text, struct Color color);
    bool isMouseTouching();
    void render(Coordinate dst);
    void render();
    Size getSize();
    void setCoordinate(Coordinate pos);
};

#endif