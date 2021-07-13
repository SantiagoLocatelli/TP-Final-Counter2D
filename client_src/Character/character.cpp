#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


#define PHASE_SHIFT 90
const SDL_Rect SRC_KNIFE = { 0, 0, 32, 32};
const SDL_Rect SRC_BIG_GUN = { 0, 64, 32, 32};
const SDL_Rect SRC_DEFUSER = { 32, 32, 32, 32};
const SDL_Rect SRC_PISTOL = {32, 32, 32, 32};

Character::Character(PlayerInfo player, SdlTexture& texture, Weapon* weapon):
    texture(texture), player(player), weapon(weapon){}


SDL_Rect Character::getSourceTexture(){
    if (this->player.weapon.type == KNIFE) {
        return SRC_KNIFE;
    } else if (this->player.weapon.type == RIFLE || this->player.weapon.type == SHOTGUN || this->player.weapon.type == SNIPER) {
        return SRC_BIG_GUN;
    } 
    return SRC_PISTOL;
}

void Character::render(Coordinate cam){
    SDL_Rect dstPj = {this->player.pos.x - cam.x - this->player.size.w/2, this->player.pos.y - cam.y - this->player.size.h/2, this->player.size.w, this->player.size.h};
    SDL_Rect srcPj = getSourceTexture();

    Coordinate dstWp = {this->player.weapon.pos.x - this->player.weapon.size.w/2 - cam.x,
                        this->player.weapon.pos.y - this->player.weapon.size.h/2 - cam.y};
    Coordinate dstAnim = {this->player.weapon.posAnim.x - this->player.weapon.size.w/2 - cam.x,
                          this->player.weapon.posAnim.y - this->player.weapon.size.h/2 - cam.y};
                        
    Size sizeWp = {this->player.weapon.size.w, this->player.weapon.size.h};

    //this->info.pos.x - this->info.size.w/2 - cam.x, this->info.pos.y - this->info.size.h/2 - cam.y, this->info.size.w, this->info.size.h
    this->weapon->render(dstWp, dstAnim, sizeWp, this->player.degrees, this->player.shooting);
    this->texture.render(dstPj.x, dstPj.y, dstPj.w, dstPj.h, &srcPj, this->player.degrees + PHASE_SHIFT);
}


void Character::update(PlayerInfo info, Weapon* weapon){
    this->player.dead = info.dead;
    if (info.dead) return;

    this->weapon = weapon;

    this->player.shooting = info.shooting;
    this->player.degrees = info.degrees;
    this->player.weapon = info.weapon;
    this->player.pos = info.pos;
    this->player.size = info.size;
    // printf("coordenada x: %i, y: %i\n", info.pos.x, info.pos.y);
}

WeaponType Character::getWeaponType(){return this->player.weapon.type;}
bool Character::isDead(){return this->player.dead;}
int Character::getPosY(){return this->player.pos.y;}
int Character::getPosX(){return this->player.pos.x;}
SDL_Rect Character::getRect(){return {this->player.pos.x, this->player.pos.x, this->player.size.w, this->player.size.h};}
float Character::getDegrees(){return this->player.degrees;}
PlayerInfo Character::getInfo(){return this->player;}

// Character& Character::operator=(Character&& other){
//     this->texture = other.texture;
//     this->player = other.player;
//     this->weapon = other.weapon;
//     return *this;
// }

// Character::Character(Character&& other):texture(other.texture), weapon(other.weapon){
//     this->player = other.player;
// }

Character& Character::operator=(const Character& other){
    this->texture = other.texture;
    this->player = other.player;
    this->weapon = other.weapon;
    return *this;
}

Character::Character(const Character& other):texture(other.texture), weapon(other.weapon){
    this->player = other.player;
}