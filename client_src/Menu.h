#ifndef __MENU_H__
#define __MENU_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/TextTexture.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Protocol.h"
#include "../common_src/Event.h"
#include "levelInfo.h"
#include <list>
#include <map>
#include <memory>

class Menu{

private: 

    SdlWindow window;
    SdlRenderer renderer;
    Size size;
    
    SdlTexture background;
    Protocol& server;

    void creatGame(bool& joined_game);
    void joinGame(bool& joined_game);

    void loadMaps(std::map<std::string, TextTexture*>& maps);
    void renderCreatMenu(std::map<std::string, TextTexture*>& maps,
        bool mapSelected, bool nameSelected, std::string nameGame,
        int players, TextTexture& back, TextTexture& confirm, TextTexture& title);
    void renderJoinMenu(TextTexture& title, TextTexture& buttonBack, std::map<std::string, std::unique_ptr<TextTexture>>& options);
    void renderInitMenu(TextTexture& quitButton, TextTexture& creatButton, TextTexture& joinButton);
public:

    Menu(Size windowSize, Protocol& server);
    ~Menu();
    void run(bool& joined_game);
};

#endif