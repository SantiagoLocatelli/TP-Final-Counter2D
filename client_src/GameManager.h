#ifndef __GAME_H__
#define __GAME_H__

#include "Character/character.h"
#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../client_src/Character/camera.h"
#include <map>
#include <vector>

struct Color {
    uint8_t r, g, b;
};


class GameManager {
private:

    SdlWindow window;
    SdlRenderer renderer;

    LevelInfo level;
    ModelInfo model;

    // vector o lista de texturas
    
    // provisorio {
    std::vector<SdlTexture> textures;
    // }


    Camera cam;
    std::vector<Character> players;
    Stencil stencil;

    void renderPlayers();
    void renderBoxes();

public:

    GameManager(MapInfo map, ModelInfo model, int window_w, int window_h);
    void addPlayer(const char* pathTexture, struct Color color, int index);
    void addTexture(const char* pathTexture, struct Color color);
    void render();
    void initializeGame(ModelInfo model);
    void update(ModelInfo model);
    int getRelativePlayerPosX();
    int getRelativePlayerPosY();
};

#endif
