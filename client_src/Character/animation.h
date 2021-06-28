#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../Sdl/sdl_texture.h"
#define FRAME_RATE 1000000.0f/25.0f

class Animation {
private:
    const SdlTexture& texture;
    int numFrames;
    int currentFrame = 0;
    int size;
    float elapsed = 0.0f;

public:
    Animation(const SdlTexture& texture);
    ~Animation() = default;
    void update(float dt);
    void render(SDL_Rect dst, double degrees);
    void advanceFrame();
};

#endif
