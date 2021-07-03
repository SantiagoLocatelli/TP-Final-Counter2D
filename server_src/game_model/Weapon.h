#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"

class Player;
class World;

class Weapon{
    protected:
        Player *owner;
        World *world;
        float damage;

        virtual float calculateDamage(float distance) = 0;
    public:
        Weapon(Player *owner, World *world, float damage);
        void changeOwner(Player *newOwner);
        World *getWorld();
        virtual void toggle() = 0;
        void shootBullet(float spread);
        virtual ~Weapon() = default;
};

#endif
