#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../Sdl/sdl_texture.h"

class Animation {
private:
    const SdlTexture& texture;
    int numFrames;
    int currentFrame = 0;
    int size;
    int delay = 0;

public:
    Animation(const SdlTexture& texture);
    ~Animation() = default;
    void render(SDL_Rect dst, double degrees);
    void advanceFrame();
};

#endif
