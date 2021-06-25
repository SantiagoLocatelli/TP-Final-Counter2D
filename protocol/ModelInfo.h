#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_

#include <list>

struct Player{
    float x;
    float y;
    float angle; //En radianes
};

struct You: public Player{
    float health;
    uint16_t ammo;
};

struct Bullet{
    float start_x;
    float start_y;
    float angle; //En radianes
};

struct ModelInfo{
    You you;
    std::list<Player> players;
    std::list<Bullet> bullets;
};

#endif
