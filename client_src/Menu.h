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
    std::map<int, std::unique_ptr<TextTexture>> buttons;

    void loadButtons();
    void loadMaps(std::map<std::string, std::unique_ptr<TextTexture>>& maps);
    void createGame(bool& joined_game, bool& quit);
    void joinGame(bool& joined_game, bool& quit);

    void renderCreateMenu(std::map<std::string, std::unique_ptr<TextTexture>>& maps,
        bool mapSelected, bool nameSelected, std::string nameGame,
        int players);
    void renderJoinMenu(std::map<std::string, std::unique_ptr<TextTexture>>& options);
    void renderInitMenu();
public:

    Menu(Size windowSize, Protocol& server);
    ~Menu();
    void run(bool& joined_game);
};

#endif