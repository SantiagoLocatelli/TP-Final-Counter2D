#ifndef __SDL_WALL_H__
#define __SDL_WALL_H__
#include <SDL2/SDL.h>
#include "game_object.h"
class Wall : public GameObject{
    private:
        SDL_Rect clip;
    public:
        Wall(int x, int y, SdlRenderer& r, std::string path, SDL_Rect clip);
        void render(SDL_Rect& camera);
};
#endif
