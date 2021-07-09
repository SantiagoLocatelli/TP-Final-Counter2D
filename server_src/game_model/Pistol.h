#ifndef _PISTOL_H_
#define _PISTOL_H_

#include "Weapon.h"

class Pistol: public Weapon{
    public:
        explicit Pistol(World *world, GameConfig &config);
};

#endif
