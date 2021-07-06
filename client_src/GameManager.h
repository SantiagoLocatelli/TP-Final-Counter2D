#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "GameViewer.h"
#include "levelInfo.h"


class GameManager {
private:

    GameViewer game; 
    LevelInfo level;
    
    void updatePlayer(PlayerInfo& player, ProtPlayer prot);
    void updateBullet(BulletInfo& bullet, Bullet prot);
    void updateDrop(DropInfo& drop, ProtDrop prot);
    void updateBox(BoxInfo& box, ProtBox prot);
    LevelInfo initializeLevel(const MapInfo& map, const ModelInfo& model);

public:

    GameManager(const MapInfo& map, const ModelInfo& model, int window_w, int window_h);
    
    void update(const ModelInfo& model);
    void render();
    Coordenada getRelativePlayerPos();
    void setCrossHair(Coordenada pos);
};

#endif
