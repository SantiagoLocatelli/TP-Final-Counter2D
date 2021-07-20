#ifndef __MENU_H__
#define __MENU_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/TextTexture.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Protocol.h"
#include "../common_src/Event.h"
#include <SDL2/SDL_mixer.h>
#include "levelInfo.h"
#include <SDL2/SDL.h>
#include <memory>
#include <list>
#include <map>

enum Resolution : int {STANDARD, SEMI_HIGH, HIGH};

enum Button : int {QUIT, NEW_GAME, JOIN, BACK, CONFIRM, LABEL};


class Menu{

private: 

    SdlWindow window;
    SdlRenderer renderer;
    Size size;
    
    Mix_Music *music;
    SdlTexture background;
    Protocol& server;
    std::map<Button, std::unique_ptr<TextTexture>> buttons;


    void loadMaps(std::map<std::string, std::unique_ptr<TextTexture>>& maps);
    void loadResolutions(std::map<Resolution, std::unique_ptr<TextTexture>>& options);
    void loadButtons();

    void createGame(bool& joined_game, bool& quit, Event& event);
    void joinGame(bool& joined_game, bool& quit, Event& event);
    void makeChooseSkins(SkinType& ct, SkinType& tt);
    void makeChooseResolution(bool& quit, Size& resolution);

    void renderOptionsResolutions(std::map<Resolution, std::unique_ptr<TextTexture>>& options);
    void renderCreateMenu(std::map<std::string, std::unique_ptr<TextTexture>>& maps,
        bool mapSelected, bool nameSelected, std::string nameGame, int players);
    void renderJoinMenu(std::map<std::string, std::unique_ptr<TextTexture>>& options);
    void renderInitMenu(TextTexture& muteText);

    void renderLoadingMenu();
public:

    Menu(Size windowSize, Protocol& server);
    ~Menu();
    void run(bool& joined_game, Size& size);
};

#endif