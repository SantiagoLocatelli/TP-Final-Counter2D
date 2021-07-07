#ifndef __PARTICLEBULLETS_H__
#define __PARTICLEBULLETS_H__

#include "../../common_src/Sdl/sdl_renderer.h"
#include "../../common_src/ModelInfo.h"
#include "levelInfo.h"

class ParticleBullets{
private:

    Coordenada pos;
    Coordenada dst;
    SdlRenderer& renderer;

public:

    ParticleBullets(SdlRenderer& renderer);
    void setTrajectory(Coordenada pos, Coordenada dst);
    void render(Coordenada cam);
};

#endif