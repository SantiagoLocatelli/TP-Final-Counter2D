#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "../../client_src/Character/camera.h"
#include "sdl_texture.h"

class Background {
    private:
        const SdlTexture& bg;
        Camera& cam;
        int level_w;
        int level_h;

    public:
        Background(const SdlTexture& texture, Camera& cam, int level_w, int level_h);
        void render();

};

#endif
