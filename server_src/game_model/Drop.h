#ifndef _DROP_H_
#define _DROP_H_

#include "Weapon.h"
#include "World.h"
class World;
class Weapon;

class Drop{
    private:
        World &world;
        Weapon *weapon;
        b2Body *body;
        b2Fixture *fixture;

    public:
        Drop(World &world, float x, float y, Weapon *weapon);

        Weapon *getWeapon();
        std::array<float, 2> getPosition();
        Weapon *getTaken();


        Drop(const Drop&) = delete;
        Drop& operator=(const Drop&) = delete;
};

#endif
