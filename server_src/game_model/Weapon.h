#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"
#include "../../common_src/WeaponType.h"

class Player;
class World;

class Weapon{
    protected:
        Player *owner;
        World *world;
        float damage;
        WeaponType type;

        virtual float calculateDamage(float distance) = 0;
    public:
        Weapon(World *world, float damage, WeaponType type);
        void changeOwner(Player *newOwner);
        World *getWorld();
        WeaponType getType();
        virtual void toggle() = 0;
        void shootBullet(float spread);
        virtual ~Weapon() = default;
};

#endif
