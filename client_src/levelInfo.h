#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <list>
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

struct WeaponInfo {
    Coordenada pos;
    Size size;
    Coordenada posAnim;
    WeaponType type;
};

struct PlayerInfo {
    Coordenada pos;
    Size size;
    float degrees;
    bool shooting;
    bool dead;
    WeaponInfo weapon;
};

struct MainPlayerInfo: public PlayerInfo {
    float health;
    int ammo;
};

struct BulletInfo {
    Coordenada pos;
    Coordenada dst;
};

struct TileInfo {
    uint8_t id;
    Coordenada pos;
    Size size;
};

struct LevelInfo{
    int height;
    int width;
    
    std::vector<TileInfo> tiles;
    std::list<BoxInfo> bombSites;
    std::list<BoxInfo> spawnSites;

    MainPlayerInfo mainPlayer;
    std::list<DropInfo> drops;
    std::list<PlayerInfo> players;
    std::list<BulletInfo> bullets;
};

#endif