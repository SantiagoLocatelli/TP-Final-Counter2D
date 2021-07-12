#ifndef _BOMB_H_
#define _BOMB_H_

#include "World.h"
#include "GameConfig.h"

class Bomb: public Weapon{
    private:
        float plantTime;
        
    public:
        Bomb(World *world, GameConfig &config);
        void toggle() override;
        void reload() override;
        void step(float delta) override;
};

#endif
