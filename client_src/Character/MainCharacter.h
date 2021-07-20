#ifndef __MAIN_CHARACTER_H__
#define __MAIN_CHARACTER_H__

#include "../levelInfo.h"
#include "Character.h"
#include "Crosshair.h"
#include "Stencil.h"

class MainCharacter: public Character {

private:

    CrossHair cr;
    Stencil st;
    MainPlayerInfo player;

public:

    MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st, Weapon* weapon);
    void render(Coordinate cam);
    void update(MainPlayerInfo info, Weapon* weapon);
    void setCrossHair(Coordinate pos);
    MainPlayerInfo getMainPlayerInfo();
};


#endif