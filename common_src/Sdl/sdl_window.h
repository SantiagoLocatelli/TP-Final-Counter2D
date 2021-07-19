#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include <SDL2/SDL.h>
#include <string>

class SdlWindow{
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        int mWidth;
        int mHeight;


    public:
        SdlWindow(std::string name, int width, int height);
        SDL_Renderer* createRender();
        int getHeight();
        int getWidth();
        SDL_Window* getWindow();
        void setFullScreen();
        void setFullScreenOf();
        void setTitle(std::string title);
        void free();
        ~SdlWindow();
};
#endif
