#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include <SDL2/SDL.h>
#include <string>

class SdlWindow{
    private:
        SDL_Window* mWindow;
        int mWidth;
        int mHeight;

    public:
        SdlWindow(std::string name, int width, int height);
        SDL_Renderer* createRender();
        int getHeight();
        int getWidth();
        ~SdlWindow();
};
#endif
