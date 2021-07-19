#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/ModelInfo.h"
#include "../common_src/MapInfo.h"
#include "levelInfo.h"
#include <map>

class GameManager {
private:

    Size pixelsPerMeter;
    std::map<int, Size> sizeWeapons;

    void translateRect(BoxInfo& box, RectArea rect);
    void updateBomb(BombInfo& bomb, ProtBomb prot);
    void updatePlayer(PlayerInfo& player, ProtPlayer prot);
    void updateWeapon(WeaponInfo& weapon, ProtPlayer prot, Coordinate player);
    void updateDrop(DropInfo& drop, ProtDrop prot);
    void updateBullet(BulletInfo& bullet, Bullet prot);
    void translatePosition(Coordinate& coord, Position pos);
public:

    GameManager(Size windowSize);
    
    void initializeLevel(LevelInfo& level, const MapInfo& map, const ModelInfo& model);
    void updatedLevel(LevelInfo& level, const ModelInfo& model);
};

#endif
