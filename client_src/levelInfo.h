#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <list>
#include "../../common_src/ModelInfo.h"

struct Coordenada {
    int x;
    int y;
};

struct Size {
    int w; 
    int h;
};

struct Box {
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

    std::list<Box> boxes;

    std::list<DropInfo> drops;

    std::list<PlayerInfo> players;

    std::list<BulletInfo> bullets;
};

#endif