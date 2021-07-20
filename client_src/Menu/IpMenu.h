#ifndef __IP_MENU_H__
#define __IP_MENU_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/TextTexture.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_window.h"
#include <SDL2/SDL.h>
#include <memory>
#include <map>

class IpMenu{
    private:
        SdlWindow window;
        SdlRenderer renderer;
        Mix_Music *music;
        SdlTexture background;
        bool renderText, isPort;
        std::string ip, port, variableText;
        std::map<int, std::unique_ptr<TextTexture>> map;
    public:
        IpMenu();
        ~IpMenu();
        void start();
        std::string getIp();
        std::string getPort();
};
#endif
