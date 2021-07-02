#ifndef __GAME_H__
#define __GAME_H__

#include "Character/character.h"
#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../client_src/Character/camera.h"

class GameManager {
private:


    SdlWindow window;
    SdlRenderer renderer;

    LevelInfo level;
    ModelInfo model;
    //GameInfo game;
    Character pj;
    Camera cam;


    void renderPlayers();
    void renderBoxes();

public:

    GameManager(MapInfo map, ModelInfo model, int window_w, int window_h, Character pj);
    void render();
    void update(ModelInfo model);
    int getRelativePlayerPosX();
    int getRelativePlayerPosY();
};

#endif
