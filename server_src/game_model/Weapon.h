#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"
#include "../../common_src/Utils.h"
#include "GameConfig.h"
#include "RayCaster.h"
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
        GameConfig &config;
        int bullets;
        float reloadTime;
        float shootTime;
        bool toggled;
        RayCaster rayCaster;

        virtual float calculateDamage(float distance);
    public:
        Weapon(World *world, GameConfig &config, WeaponType type, WeaponSlot slot);
        void changeOwner(Player *newOwner);
        World *getWorld();
        WeaponType getType();
        WeaponSlot getSlot();
        int getAmmo();
        virtual void toggle();
        virtual void reload();
        virtual void step(float delta);
        void shootBullet();
        int getPrice();
        virtual ~Weapon() = default;
};

#endif
