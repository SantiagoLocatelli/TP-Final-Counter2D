#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../common_src/Sdl/sdl_texture.h"

class Animation {
private:
    SdlTexture texture;
    int numFrames;
    int currentFrame = 0;
    int size;
    int delay = 0;

public:
    Animation(SdlTexture texture);
    // Animation();
    ~Animation() = default;
    void render(SDL_Rect dst, double degrees);
    void advanceFrame();


    Animation& operator=(Animation&&);
    Animation(Animation&& other);
};

#endif
