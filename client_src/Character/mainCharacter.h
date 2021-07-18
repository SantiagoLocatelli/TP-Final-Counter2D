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
    int money;

public:

    MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st, Weapon* weapon);
    void render(Coordinate cam);
    void update(MainPlayerInfo info, Weapon* weapon);
    void setCrossHair(Coordinate pos);
};


#endif