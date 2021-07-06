#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


Character::Character(PlayerInfo player, SdlTexture& texture):
    player(player), an(texture){}


void Character::render(int camX, int camY){
    SDL_Rect dst = {this->player.pos.x - camX - this->player.size.w/2, this->player.pos.y - camY - this->player.size.h/2, this->player.size.w, this->player.size.h};
    this->an.render(dst, this->player.degrees);
}


void Character::update(PlayerInfo info){
    this->player.dead = info.dead;
    if (this->player.dead) return;

    // para que cambia de frame solo si avanza
    if (this->player.pos.x != info.pos.x || this->player.pos.y != info.pos.y) {

        this->an.advanceFrame();
    }
    this->player = info;
}

bool Character::isDead(){return this->player.dead;}
int Character::getPosY(){return this->player.pos.y;}
int Character::getPosX(){return this->player.pos.x;}
SDL_Rect Character::getRect(){return {this->player.pos.x, this->player.pos.x, this->player.size.w, this->player.size.h};}
WeaponType Character::getIdWeapon(){return this->player.weapon;}
float Character::getDegrees(){return this->player.degrees;}

Character& Character::operator=(Character&& other){
    this->an = std::move(other.an);
    this->player = other.player;
    return *this;
}

Character::Character(Character&& other): 
    an(std::move(other.an)){
    this->player = other.player;
}
