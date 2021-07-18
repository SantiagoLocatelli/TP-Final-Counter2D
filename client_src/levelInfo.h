#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <list>
#include <vector>
#include "../../common_src/ModelInfo.h"
#include "Managers/SoundEffects.h"

struct Color {
    uint8_t r,g,b;
};

struct Coordinate {
    int x;
    int y;
};

struct Size {
    int w; 
    int h;
};

struct BoxInfo {
    Coordinate pos;
    Size size;
};

struct DropInfo {
    Coordinate pos;
    Size size;
    WeaponType type;
};

struct WeaponInfo {
    Coordinate pos;
    Size size;
    Coordinate posAnim;
    WeaponType type;
    WeaponEffect sound;
};

struct PlayerInfo {
    Coordinate pos;
    Size size;
    float degrees;
    bool shooting;
    bool dead;
    Team team;
    WeaponInfo weapon;
    std::array<WeaponType, 4> weapons;
    WeaponSlot currentSlot;
    std::list<PlayerEffect> sounds;
};

struct MainPlayerInfo: public PlayerInfo {
    float health;
    int ammo;
    bool damaged;
    int money;
};

struct BulletInfo {
    Coordinate pos;
    Coordinate dst;
};

struct TileInfo {
    uint8_t id;
    Coordinate pos;
    Size size;
};

struct BombInfo {
    bool planted; // si es falso todos los otros campo son invalidos
    bool defused;
    Coordinate pos;
    float time;
};



struct LevelInfo{
    Size size;
    
    BombInfo bomb;
    float timeRemaining;
    ProtState state;

    std::vector<TileInfo> tiles;
    std::list<BoxInfo> bombSites;
    std::list<BoxInfo> spawnSites;

    MainPlayerInfo mainPlayer;
    std::list<DropInfo> drops;
    std::list<PlayerInfo> players;
    std::list<BulletInfo> bullets;
};

#endif