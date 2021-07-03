#ifndef __PARTICLEBULLETS_H__
#define __PARTICLEBULLETS_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/ModelInfo.h"
#include "levelInfo.h"

class ParticleBullets{
private:

    int posX = 0, posY = 0;
    int distance = 0;
    float degrees = 0.0;
    SdlTexture particle;

public:

    ParticleBullets(SdlRenderer& renderer);
    void setTrajectory(LevelInfo level, Bullet bullet);
    void render();
};

#endif