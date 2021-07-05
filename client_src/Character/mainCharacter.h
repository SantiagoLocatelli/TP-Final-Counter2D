#ifndef __MAIN_CHARACTER_H__
#define __MAIN_CHARACTER_H__

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

    MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st);
    void render(Coordenada cam);
    void update(MainPlayerInfo info);
    void setCrossHair(Coordenada pos);
};


#endif