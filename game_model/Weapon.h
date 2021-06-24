#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Player.h"
#include "World.h"

class Weapon{
    private:
        Player &owner;
        World &world;
        float damage;

        float calculateDamage(float distance);
    public:
        Weapon(Player &owner, World &world);
        void activate(float angle);
};

#endif
