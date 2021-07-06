#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <list>
#include "../../common_src/ModelInfo.h"

struct Coordenada {
    int x;
    int y;

    // Coordenada& operator=(const Coordenada& other){
    //     this->x = other.x;
    //     this->y = other.y;
    //     return *this;
    // }
};

struct Size {
    int w; 
    int h;

    // Size& operator=(const Size& other){
    //     this->w = other.w;
    //     this->h = other.h;
    //     return *this;
    // }
};

struct BoxInfo {
    Coordenada pos;
    Size size;

    // BoxInfo(){
    //     pos.x = 0;
    //     pos.y = 0;
    //     size.w = 0;
    //     size.h = 0;
    // }

    // BoxInfo(const BoxInfo& other) {
    //     this->pos = other.pos;
    //     this->size = other.size;
    // }

    // BoxInfo(BoxInfo &&other){
    //     this->pos = std::move(other.pos);
    //     this->size = std::move(other.size);
    // }
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

    // PlayerInfo(const PlayerInfo& other){
    //     this->pos.x = other.pos.x;
    //     this->pos.x = other.pos.y;
    //     this->size.w = other.size.w;
    //     this->size.h = other.size.h;
    //     this->weapon = other.weapon;
    //     this->degrees = other.degrees;
    //     this->dead = other.dead;
    // }

    // PlayerInfo& operator=(const PlayerInfo& other){
    //     this->pos.x = other.pos.x;
    //     this->pos.x = other.pos.y;
    //     this->size.w = other.size.w;
    //     this->size.h = other.size.h;
    //     this->weapon = other.weapon;
    //     this->degrees = other.degrees;
    //     this->dead = other.dead;
    //     return *this;
    // }
};

struct MainPlayerInfo: public PlayerInfo {
    float health;
    int ammo;

    // MainPlayerInfo& operator=(const MainPlayerInfo& other){
    //     this->pos = other.pos;
    //     this->size = other.size;
    //     this->weapon = other.weapon;
    //     this->degrees = other.degrees;
    //     this->dead = other.dead;
    //     this->ammo = other.ammo;
    //     this->health = other.health;
    //     return *this;
    // }
};

struct BulletInfo {
    Coordenada pos;
    Coordenada dst;
};

struct LevelInfo{
    int height;
    int width;
    
    MainPlayerInfo mainPlayer;

    std::list<BoxInfo> boxes;

    std::list<DropInfo> drops;

    std::list<PlayerInfo> players;

    std::list<BulletInfo> bullets;


    // LevelInfo(){
        
    // }
};

#endif