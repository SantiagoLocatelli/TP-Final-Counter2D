#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "camera.h"
#include "sdl_texture.h"

class Background {
    private:
        const SdlTexture& bg;
        Camera& cam;
    public:

        Background(const SdlTexture& texture, Camera& cam);
        void render();

};

#endif
