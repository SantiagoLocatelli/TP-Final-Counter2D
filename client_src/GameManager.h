#ifndef __GAME_H__
#define __GAME_H__

#include "Character/character.h"
#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../client_src/Character/camera.h"
#include <map>

struct Color {
    uint8_t r, g, b;
};


class GameManager {
private:

    SdlWindow window;
    SdlRenderer renderer;

    LevelInfo level;
    ModelInfo model;
    //GameInfo game;

    // vector o lista de texturas
    
    Camera cam;
    // el primer jugador siempre es el que 
    std::map<int,Character> players;
    Stencil stencil;

    void renderPlayers();
    void renderBoxes();

public:

    GameManager(MapInfo map, ModelInfo model, int window_w, int window_h);
    void addPlayer(const char* pathTexture, struct Color color);
    void addTexture(const char* pathTexture, struct Color color);
    void render();
    void update(ModelInfo model);
    int getRelativePlayerPosX();
    int getRelativePlayerPosY();
};

#endif
