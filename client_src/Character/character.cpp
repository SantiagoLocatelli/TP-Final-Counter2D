#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


Character::Character(int width, int height, SdlTexture texture)
    : an(std::move(texture)), degrees(0.0), dead(false){

    this->area.x = 0;
    this->area.y = 0;
    this->area.w = width;
    this->area.h = height;
}


void Character::render(int camX, int camY){
    SDL_Rect dst = {this->area.x - camX - this->area.w/2, this->area.y - camY - this->area.h/2, this->area.w, this->area.h};
    this->an.render(dst, this->degrees);
}


void Character::update(const Prot_Player you, const LevelInfo level, float health, uint16_t ammo){

    this->dead = you.dead;
    if (this->dead) return;

    this->degrees = Math::radiansToDegrees(you.angle);
    int x = Math::ruleOfThree(you.x, level.w_meters, level.width);
    int y = Math::ruleOfThree(you.y, level.h_meters, level.height);

    // para que cambia de frame solo si avanza
    if (this->area.x != x || this->area.y != y) {

        this->an.advanceFrame();
    }
    this->area.x = x;
    this->area.y = y;
}

bool Character::isDead(){return this->dead;}
int Character::getPosY(){return this->area.y;}
int Character::getPosX(){return this->area.x;}
SDL_Rect Character::getRect(){return this->area;}

Character& Character::operator=(Character&& other){
    this->area = other.area;
    this->an = std::move(other.an);
    this->degrees = other.degrees;
    return *this;
}

Character::Character(Character&& other): 
    an(std::move(other.an)){
    this->area = other.area;
    this->degrees = other.degrees;
}
