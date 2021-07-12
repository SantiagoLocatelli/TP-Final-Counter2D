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
    WeaponInfo info;

public:
    Weapon(SdlTexture& weapon, SdlTexture& anim, Size size);
    void update(WeaponInfo info);
    void render(Coordenada cam, float degrees, bool animated);

    Weapon& operator=(const Weapon&);
    Weapon(const Weapon&);

};

#endif