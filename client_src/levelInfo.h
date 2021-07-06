#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <vector>
#include "../../common_src/ModelInfo.h"

struct Coordenada {
    int x;
    int y;
};

struct Size {
    int w; 
    int h;
};

struct BoxInfo {
    Coordenada pos;
    Size size;
};

struct DropInfo {
    Coordenada pos;
    Size size;
    WeaponType type;
};

struct PlayerInfo {
    Coordenada pos;
    Size size;
    WeaponType weapon;
    float degrees;
    bool dead;
};

struct MainPlayerInfo: public PlayerInfo {
    float health;
    int ammo;
};

struct BulletInfo {
    Coordenada pos;
    Coordenada dst;
};

struct LevelInfo{
    int height;
    int width;
    
    MainPlayerInfo mainPlayer;

    std::vector<BoxInfo> boxes;

    std::vector<DropInfo> drops;

    std::vector<PlayerInfo> players;

    std::vector<BulletInfo> bullets;

};

#endif