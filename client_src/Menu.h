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


class Menu{

private: 

    SdlWindow window;
    SdlRenderer renderer;
    Size size;
    std::map<std::string, TextTexture*> maps;
    std::map<int, TextTexture*> buttons;
    SdlTexture background;
    Protocol& server;

    void loadMaps();
    void loadButtons();
    void creatGame(bool& joined_game);
    void joinGame(bool& joined_game);

    void renderCreatMenu(bool mapSelected, bool nameSelected, bool playersSelected, std::string nameGame, int players);
    void renderJoinMenu(TextTexture& title, TextTexture& buttonBack, std::map<std::string, TextTexture*>& options);
    void renderInitMenu();
public:

    Menu(Size windowSize, Protocol& server);
    ~Menu();
    void run();
};

#endif