#include "MainCharacter.h"

MainCharacter::MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st, Weapon* weapon):
    Character(player, pjTexture, weapon), cr(std::move(cr)), st(std::move(st)){}

void MainCharacter::render(Coordinate cam){
    this->cr.render();
    this->st.render(cam);
    Character::render(cam);
}

void MainCharacter::update(MainPlayerInfo info, Weapon* weapon){
    this->player.ammo = info.ammo;
    this->player.health = info.health;
    this->player.money = info.money;
    this->st.setPosition(info.pos, info.degrees); 
    Character::update(info, weapon);
}

void MainCharacter::setCrossHair(Coordinate pos){
    this->cr.setPosition(pos);
}

MainPlayerInfo MainCharacter::getMainPlayerInfo(){return this->player;}
