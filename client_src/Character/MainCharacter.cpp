#include "MainCharacter.h"

MainCharacter::MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st, Weapon* weapon):
    Character(player, pjTexture, weapon), cr(std::move(cr)), st(std::move(st)),
    health(player.health), ammo(player.ammo), money(0){}

void MainCharacter::render(Coordinate cam){
    this->cr.render();
    this->st.render(cam);
    Character::render(cam);
}

void MainCharacter::update(MainPlayerInfo info, Weapon* weapon){
    this->ammo = info.ammo;
    this->health = info.health;
    this->money = info.money;
    this->st.setPosition(info.pos, info.degrees);
    Character::update(info, weapon);
}

void MainCharacter::setCrossHair(Coordinate pos){
    this->cr.setPosition(pos);
}
