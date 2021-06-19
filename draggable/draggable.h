#ifndef _DRAGGABLE_H_
#define _DRAGGABLE_H_
#include <SDL2/SDL.h>
#include <string>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_renderer.h"
#include "../Sdl/sdl_window.h"
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
