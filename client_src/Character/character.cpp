#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


#define PHASE_SHIFT 90

Character::Character(PlayerInfo player, SdlTexture& texture):
    player(player), texture(texture)/*an(texture)*/{}


void Character::render(int camX, int camY){
    SDL_Rect dst = {this->player.pos.x - camX - this->player.size.w/2, this->player.pos.y - camY - this->player.size.h/2, this->player.size.w, this->player.size.h};
    // this->an.render(dst, this->player.degrees);
    SDL_Rect src = { 0, 0, 32, 32};
    // printf("destino x: %i\n", dst.x);
    // printf("destino y: %i\n", dst.y);
    // printf("dst w: %i\n", dst.w);
    // printf("dst h: %i\n", dst.h);
    // printf("cam x: %i\n", camX);
    // printf("cam y: %i\n", camY);
    this->texture.render(dst.x, dst.y, dst.w, dst.h, &src, this->player.degrees + PHASE_SHIFT);
}


void Character::update(PlayerInfo info){
    this->player.dead = info.dead;
    if (this->player.dead) return;

    // para que cambia de frame solo si avanza
    if (this->player.pos.x != info.pos.x || this->player.pos.y != info.pos.y) {

        // this->an.advanceFrame();
    }
    this->player.degrees = info.degrees;
    this->player.weapon = info.weapon;
    printf("pos x: %i\n",  this->player.pos.x);
    this->player.pos.x = info.pos.x;
    printf("pos y: %i\n\n", this->player.pos.y);
    this->player.pos.y = info.pos.y;
    this->player.size.w = info.size.w;
    this->player.size.h = info.size.h;
}

bool Character::isDead(){return this->player.dead;}
int Character::getPosY(){return this->player.pos.y;}
int Character::getPosX(){return this->player.pos.x;}
SDL_Rect Character::getRect(){return {this->player.pos.x, this->player.pos.x, this->player.size.w, this->player.size.h};}
WeaponType Character::getIdWeapon(){return this->player.weapon;}
float Character::getDegrees(){return this->player.degrees;}

Character& Character::operator=(Character&& other){
    // this->an = other.an;
    this->texture = other.texture;
    this->player = other.player;
    return *this;
}

Character::Character(Character&& other):texture(other.texture)/* 
    an(other.an)*/{
    this->player = other.player;
}
