#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"
#include "../../common_src/WeaponUtils.h"
#include "GameConfig.h"
#include <map>
#include <string>

class Player;
class World;

class Weapon{
    protected:
        Player *owner;
        World *world;
        WeaponType type;
        WeaponSlot slot;
        std::map<std::string, float> config;
        int bullets;

        virtual float calculateDamage(float distance);
    public:
        Weapon(World *world, GameConfig &config, WeaponType type, WeaponSlot slot);
        void changeOwner(Player *newOwner);
        World *getWorld();
        WeaponType getType();
        WeaponSlot getSlot();
        virtual void toggle();
        virtual void reload();
        void shootBullet();
        virtual ~Weapon() = default;
};

#endif
