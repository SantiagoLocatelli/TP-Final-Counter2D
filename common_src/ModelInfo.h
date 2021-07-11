#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_

#include <list>
#include <stdint.h>
#include "Utils.h"

struct Position{
    float x;
    float y;
};

struct ProtPlayer{
    bool dead; //IMPORTANTE: Si el jugador está muerto los otros atributos son inválidos!!
    Position pos;
    float angle; //En radianes
    WeaponType weapon;
    bool shooting;
    Team team;
};

struct You: public ProtPlayer{
    float health;
    uint16_t ammo;
};

struct Bullet{
    Position pos;
    float angle; //En radianes
    float distance;
};

struct ProtDrop{
    WeaponType type;
    Position pos;
};

struct ModelInfo{
    You you;
    std::list<ProtPlayer> players;
    std::list<Bullet> bullets;
    std::list<ProtDrop> drops;
    bool game_ended;
};

#endif
