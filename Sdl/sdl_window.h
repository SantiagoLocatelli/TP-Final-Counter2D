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
        
        int mWindowID;

        //Window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;
        bool mShown;

    public:
        SdlWindow(std::string name, int width, int height);
        SDL_Renderer* createRender();
        int getHeight();
        int getWidth();
        void handleEvent(SDL_Event& e);
        void render();
        void focus();
        ~SdlWindow();


        //Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();

        SDL_Window* getWindow();
};
#endif
