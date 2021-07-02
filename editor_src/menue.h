#ifndef __MENUE_H__
#define __MENUE_H__
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/button.h"
class Menue{
    private:
        std::vector<std::unique_ptr<SdlTexture>> options;

    public:
        Menue(SdlRenderer& renderer, SDL_Rect bombSiteA, SDL_Rect bombSiteB, SDL_Rect spawnSiteT, SDL_Rect spawnSiteCT);
        void init();
};
#endif
