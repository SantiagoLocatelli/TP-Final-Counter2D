#ifndef __DRAGGABLE_H__
#define __DRAGGABLE_H__
#include <SDL2/SDL.h>
#include <string>
#include "sdl_texture.h"
class Draggable : public SdlTexture{
    private:
        int posX, posY;
        SDL_Point clickOffset;
        SDL_Point mousePos;
        bool leftMouseButtonDown, selected;
    public:
        Draggable(SdlRenderer& renderer, std::string path, int x, int y);
        Draggable(SdlRenderer& renderer, std::string path, int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        void handleEvent(SDL_Event* event, SDL_Rect camera);
        void render(int width, int height);
        void render(SDL_Rect camera);
        bool isTouching(SDL_Rect camera);
        SDL_Rect getBox();
        int getPosX();
        int getPosY();
};
#endif
