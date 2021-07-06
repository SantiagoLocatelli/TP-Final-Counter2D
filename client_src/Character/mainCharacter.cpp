#include "mainCharacter.h"

MainCharacter::MainCharacter(MainPlayerInfo player, SdlTexture& pjTexture, CrossHair cr, Stencil st):
    Character(player, pjTexture), cr(std::move(cr)), st(std::move(st)),
    health(player.health), ammo(player.ammo){}

void MainCharacter::render(Coordenada cam){
    printf("rendirizando el main character\n");
    this->cr.render();
    this->st.render(cam.x, cam.y);
    Character::render(cam.x, cam.y);
}

void MainCharacter::update(MainPlayerInfo info){
    this->ammo = info.ammo;
    this->health = info.health;
    this->st.setPosition(info.pos, info.degrees);
    Character::update(info);
}

void MainCharacter::setCrossHair(Coordenada pos){
    this->cr.setPosition(pos);
}
