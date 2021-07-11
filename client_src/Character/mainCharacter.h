#ifndef __MAIN_CHARACTER_H__
#define __MAIN_CHARACTER_H__

#include "../levelInfo.h"
#include "character.h"
#include "crosshair.h"
#include "stencil.h"

class MainCharacter: public Character {

private:

    CrossHair cr;
    Stencil st;
    float health;
    int ammo;

public:

    MainCharacter(MainPlayerInfo player, SdlTexture pjTexture, CrossHair cr, Stencil st, Weapon weapon);
    void render(Coordenada cam);
    void update(MainPlayerInfo info, Weapon weapon);
    void setCrossHair(Coordenada pos);
};


#endif