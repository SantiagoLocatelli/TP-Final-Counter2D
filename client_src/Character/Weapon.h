#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../SoundEffects.h"
#include "../levelInfo.h"
#include <string>
#include <list>


class Weapon {
private:

    SdlTexture& weapon;
    SdlTexture& anim;

public:
    Weapon(SdlTexture& weapon, SdlTexture& anim, Size size);
    void render(Coordinate dst, Size size, float degrees, bool animated);

    Weapon& operator=(const Weapon&);
    Weapon(const Weapon&);

    Weapon& operator=(Weapon&&);
    Weapon(Weapon&&);
};

#endif