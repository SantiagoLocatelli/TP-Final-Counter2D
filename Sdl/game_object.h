#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include "sdl_texture.h"
#include "sdl_renderer.h"
#include <SDL2/SDL.h>
#include <string>

class GameObject{
    private:
        SdlTexture texture;
        SDL_Rect mBox;
    public:
        GameObject(int x, int y, SdlRenderer& r, std::string path);
        void render(int x, int y);
        void render(SDL_Rect& camera, SDL_Rect clip);
        virtual void render(SDL_Rect& camera){}
        SDL_Rect getBox();
};
#endif
