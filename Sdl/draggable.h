#ifndef _DRAGGABLE_H_
#define _DRAGGABLE_H_
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
        void handleEvent(SDL_Event* event);
        void render();
        bool isToching();
};
#endif
