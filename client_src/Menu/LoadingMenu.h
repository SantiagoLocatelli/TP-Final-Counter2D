#ifndef __LOADING_MENU_H__
#define __LOADING_MENU_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/TextTexture.h"
#include "../common_src/Sdl/sdl_window.h"
#include <SDL2/SDL_mixer.h>

class LoadingMenu{
private:

    SdlWindow window;
    SdlRenderer renderer;
    SdlTexture background;
    SdlTexture oldLady;
    Mix_Chunk* shot;
    TextTexture textLoading;

public:

    LoadingMenu(Size window);
    ~LoadingMenu();

    void run(bool& ready);

    LoadingMenu& operator=(const LoadingMenu&) = delete;
    LoadingMenu(const LoadingMenu&) = delete;
    LoadingMenu& operator=(LoadingMenu&& other) = delete;
};

#endif