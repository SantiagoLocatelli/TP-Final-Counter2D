#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "levelInfo.h"
#include "Character/Weapon.h"
#include <vector>
#include <map>




class GameManager {
private:


    LevelInfo level;
    ModelInfo model;

    // vector o lista de texturas



    
    void renderPlayers(int camX, int camY);
    void renderBoxes(int camX, int camY);

    void renderShots(int camX, int camY);
    void renderWeapons(int camX, int camY);
    void addPlayer(const char* pathTexture, struct Color color);
    void initializeGame(ModelInfo model);
    // ver si es necesaria
    void addTexture(const char* pathTexture, struct Color color);
    void loadWeapons();

public:

    GameManager(MapInfo map, ModelInfo model);
    ~GameManager();
    
    void update(ModelInfo model);

};

#endif
