#ifndef _GOD_GUN_H_
#define _GOD_GUN_H_

#include "Weapon.h"

#define GOD_GUN_DAMAGE 300

class GodGun: public Weapon{
    protected:
        float calculateDamage(float distance) override;

    public:
        GodGun(World *world);
        void toggle() override;
};

#endif
