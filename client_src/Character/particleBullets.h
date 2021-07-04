#ifndef __PARTICLEBULLETS_H__
#define __PARTICLEBULLETS_H__

#include "../../common_src/Sdl/sdl_renderer.h"
#include "../../common_src/ModelInfo.h"
#include "levelInfo.h"

class ParticleBullets{
private:

    int posX = 0, posY = 0;
    int dstPosX = 0, dstPosY = 0;
    SdlRenderer& renderer;

public:

    ParticleBullets(SdlRenderer& renderer);
    void setTrajectory(LevelInfo level, Bullet bullet);
    void render();
};

#endif