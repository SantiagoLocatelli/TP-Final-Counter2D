#ifndef _SNIPER_H_
#define _SNIPER_H_

#include "Weapon.h"

#define SNIPER_MAX_DAMAGE 90
#define SNIPER_MIN_DAMAGE 120
#define SNIPER_SPREAD 0.05
#define SNIPER_FALLOFF 0 //No pierde daño con la distancia

class Sniper: public Weapon{
    public:
        explicit Sniper(World *world);
};

#endif
