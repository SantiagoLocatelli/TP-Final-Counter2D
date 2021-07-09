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
        float maxDamage;
        float minDamage;
        float spread;
        float damageFalloff;

        WeaponType type;

        virtual float calculateDamage(float distance);
    public:
        Weapon(World *world, float maxDamage, float minDamage, float spread, float damageFalloff, WeaponType type);
        void changeOwner(Player *newOwner);
        World *getWorld();
        WeaponType getType();
        virtual void toggle();
        void shootBullet();
        virtual ~Weapon() = default;
};

#endif
