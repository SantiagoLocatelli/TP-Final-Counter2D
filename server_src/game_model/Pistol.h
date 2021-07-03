#ifndef _PISTOL_H_
#define _PISTOL_H_

#include "Weapon.h"

#define PISTOL_DAMAGE 20

class Pistol: public Weapon{
    protected:
        float calculateDamage(float distance) override;

    public:
        Pistol(Player *owner, World *world);
        void toggle() override;
};

#endif
