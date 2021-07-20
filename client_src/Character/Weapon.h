#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../Managers/SoundEffects.h"
#include "../LevelInfo.h"
#include <string>
#include <list>

class Weapon {
private:

    SdlTexture& weapon;
    SdlTexture& anim;
    WeaponType type;

public:
    Weapon(SdlTexture& weapon, SdlTexture& anim, WeaponType type);
    void render(Coordinate dstWp, Coordinate dstAnim, Size size, float degrees, bool animated);

    Weapon& operator=(const Weapon&);
    Weapon(const Weapon&);

    Weapon& operator=(Weapon&&);
    Weapon(Weapon&&);
};

#endif