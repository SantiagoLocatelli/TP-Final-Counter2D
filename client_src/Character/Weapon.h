#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include <list>

class Weapon {
private:

    SdlTexture weapon;
    // SdlTexture anim;
    int width;
    int heigth;

public:
    Weapon(SdlTexture weapon, int width, int height/*, SdlTexture anim*/);
    void update();
    void render(int posX, int posY, float degrees);
};

#endif