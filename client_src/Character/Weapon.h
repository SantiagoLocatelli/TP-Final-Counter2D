#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include "../../common_src/Sdl/SoundEffect.h"
#include "../levelInfo.h"
#include <string>
#include <list>


class Weapon {
private:

    SdlTexture& weapon;
    SdlTexture& anim;
    WeaponInfo info;
    SoundEffect& soundEffect;

public:
    Weapon(SdlTexture& weapon, SdlTexture& anim, Size size, SoundEffect& sound);
    void update(WeaponInfo info);
    void render(Coordenada cam, float degrees, bool animated);

    Weapon& operator=(Weapon&&);
    Weapon(Weapon&&);
};

#endif