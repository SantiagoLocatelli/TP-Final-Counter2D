#ifndef _PISTOL_H_
#define _PISTOL_H_

#include "Weapon.h"

#define PISTOL_MAX_DAMAGE 15
#define PISTOL_MIN_DAMAGE 25
#define PISTOL_SPREAD 0.1
#define PISTOL_FALLOFF 0.2

class Pistol: public Weapon{
    public:
        explicit Pistol(World *world);
};

#endif
