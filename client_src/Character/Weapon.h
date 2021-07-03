#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "../../common_src/Sdl/sdl_texture.h"
#include <list>

class Weapon {
private:

    int arma_actual = 0;
    // std::list<SdlTexture> weapons;


public:
    Weapon();
    void update();
    // void addWeapon(SdlTexture weapon);

    // Weapon& operator=(Weapon&&);
    // Weapon(Weapon&& other);
};

#endif