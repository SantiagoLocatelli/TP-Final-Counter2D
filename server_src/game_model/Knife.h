#ifndef _KNIFE_H_
#define _KNIFE_H_

#include "Weapon.h"

class Knife: public Weapon{
    public:
        Knife(World *world, GameConfig &config);
        void toggle() override;
        void reload() override;
};

#endif
