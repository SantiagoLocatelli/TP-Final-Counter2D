#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_

#include <list>
#include <stdint.h>

struct Prot_Player{
    float x;
    float y;
    float angle; //En radianes
};

struct You: public Prot_Player{
    float health;
    uint16_t ammo;
};

struct Bullet{
    float start_x;
    float start_y;
    float angle; //En radianes
    float distance;
};

struct ModelInfo{
    You you;
    std::list<Prot_Player> players;
    std::list<Bullet> bullets;
    bool game_ended;
};

#endif
