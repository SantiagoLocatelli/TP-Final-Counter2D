#ifndef __GAME_H__
#define __GAME_H__

#include "Character/character.h"
#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../client_src/Character/camera.h"
#include "Character/Weapon.h"
#include "crosshair.h"
#include "Character/particleBullets.h"
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

    std::vector<Weapon> weapons;

    ParticleBullets bullet;
    // provisorio {
    std::vector<SdlTexture> textures;
    // }

    CrossHair crosshair;
    Camera cam;
    std::vector<Character> players;
    Stencil stencil;

    void renderPlayers(int camX, int camY);
    void renderBoxes(int camX, int camY);
    void renderShots();
    void addPlayer(const char* pathTexture, struct Color color, int index);
    void initializeGame(ModelInfo model);
    // ver si es necesaria
    void addTexture(const char* pathTexture, struct Color color);
    void loadWeapons();

public:

    GameManager(MapInfo map, ModelInfo model, int window_w, int window_h);
    void render();
    void update(ModelInfo model);
    int getRelativePlayerPosX();
    int getRelativePlayerPosY();
    void setCrossHair(int posX, int posY);
};

#endif
