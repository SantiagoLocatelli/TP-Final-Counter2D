#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "../../common_src/Sdl/sdl_texture.h"

class Particle{
private:

    SdlTexture particle;
public:

    Particle(SdlTexture particle);
};

#endif