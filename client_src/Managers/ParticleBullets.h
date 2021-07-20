#ifndef __PARTICLEBULLETS_H__
#define __PARTICLEBULLETS_H__

#include "../../common_src/Sdl/sdl_renderer.h"
#include "../../common_src/ModelInfo.h"
#include "LevelInfo.h"

class ParticleBullets{
private:

    Coordinate pos;
    Coordinate dst;
    SdlRenderer& renderer;

public:

    ParticleBullets(SdlRenderer& renderer);
    void setTrajectory(Coordinate pos, Coordinate dst);
    void render(Coordinate cam);
};

#endif