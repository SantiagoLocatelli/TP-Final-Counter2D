#ifndef __SDL_RENDERER_H__
#define __SDL_RENDERER_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl_window.h"

class SdlRenderer{
    private:
        SDL_Renderer* mRenderer;
    
    public:
        SdlRenderer(SdlWindow* window);
        SDL_Texture* createTexture(SDL_Surface* loadedSurface);
        void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
        void clear();
        void updateScreen();
        void render(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip);
        ~SdlRenderer();
};
#endif
