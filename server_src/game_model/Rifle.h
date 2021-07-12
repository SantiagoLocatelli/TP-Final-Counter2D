#ifndef _RIFLE_H_
#define _RIFLE_H_

#include "World.h"
#include "GameConfig.h"

class Rifle: public Weapon{
    private:
        int burstShots;
    public:
        Rifle(World *world, GameConfig &config);
        void toggle() override;
        void step(float delta) override;
};

#endif
