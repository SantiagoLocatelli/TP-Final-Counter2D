#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

#include "Weapon.h"

#define SHOTGUN_BULLETS 10
#define SHOTGUN_MAX_DAMAGE 15
#define SHOTGUN_MIN_DAMAGE 20
#define SHOTGUN_SPREAD 0.4
#define SHOTGUN_FALLOFF 1


class Shotgun: public Weapon{
    public:
        explicit Shotgun(World *world);
        void toggle() override;
};

#endif
