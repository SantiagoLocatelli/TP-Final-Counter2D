#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"

class Player;
class World;

class Weapon{
    private:
        Player *owner;
        World *world;
        float damage;

        float calculateDamage(float distance);
    public:
        Weapon(Player *owner, World *world);
        void changeOwner(Player *newOwner);
        World *getWorld();
        void toggle();
};

#endif
