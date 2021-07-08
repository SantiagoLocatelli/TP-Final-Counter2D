#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include <list>
#include "../levelInfo.h"

class Weapon {
private:

    SdlTexture& weapon;
    SdlTexture& anim;
    WeaponInfo info;

public:
    Weapon(SdlTexture& weapon, SdlTexture& anim, Size size);
    void update(WeaponInfo info);
    void render(float degrees, bool animated, Coordenada center);

    Weapon& operator=(Weapon&&);
    Weapon(Weapon&&);
};

#endif