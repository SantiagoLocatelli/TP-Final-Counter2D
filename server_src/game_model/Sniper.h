#ifndef _SNIPER_H_
#define _SNIPER_H_

#include "Weapon.h"

#define SNIPER_DAMAGE 300

class Sniper: public Weapon{
    protected:
        float calculateDamage(float distance) override;

    public:
        Sniper(World *world);
        void toggle() override;
};

#endif
