#ifndef _SNIPER_H_
#define _SNIPER_H_

#include "Weapon.h"

class Sniper: public Weapon{
    public:
        explicit Sniper(World *world, GameConfig &config);
};

#endif
