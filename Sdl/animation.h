#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "sdl_texture.h"

class Animation {
private:
    const SdlTexture* texture;
    int numFrames;
    int currentFrame;
    int size;

public:
    Animation(const SdlTexture* texture);
    ~Animation();
    void update();
    void render();
};

#endif
