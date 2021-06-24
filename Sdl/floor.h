#ifndef __SDL_TILE_H__
#define __SDL_TILE_H__
#include <SDL2/SDL.h>
#include "game_object.h"
class Floor : public GameObject{
    private:
        SDL_Rect clip;
    public:
        Floor(int x, int y, SdlRenderer& r, std::string path, SDL_Rect clip);
        void render(SDL_Rect& camera);
};
#endif
