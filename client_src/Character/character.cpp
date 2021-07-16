#include "character.h"
#include "../Events/gameMath.h"
#include <utility>

#define DELAY_SOUND 6
#define PHASE_SHIFT 90
const SDL_Rect SRC_KNIFE = {0, 0, 32, 32};
const SDL_Rect SRC_BIG_GUN = {0, 64, 32, 32};
const SDL_Rect SRC_DEFUSER = {32, 32, 32, 32};
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

    this->weapon->render(dstWp, dstAnim, sizeWp, this->player.degrees, this->player.shooting);
    this->texture.render(dstPj.x, dstPj.y, dstPj.w, dstPj.h, &srcPj, this->player.degrees + PHASE_SHIFT);
}


void Character::update(PlayerInfo info, Weapon* weapon){
    this->player.sounds.clear();

    this->player.dead = info.dead;
    if (info.dead) return;

    this->weapon = weapon;

    if (!this->player.dead && info.dead) {
        this->player.sounds.push_back(DYING);
    }
    if (!Math::equalCoords(player.pos, info.pos)) {
        this->delay++;
        if (this->delay == DELAY_SOUND) {
            PlayerEffect effect = (PlayerEffect)Math::getRandomNumberBetween((int)STEP1, (int)STEP4);
            this->player.sounds.push_back(effect);
        }
        this->delay = this->delay % DELAY_SOUND;
    }

    this->player.weapon = info.weapon;
    this->player.shooting = info.shooting;
    if (info.shooting) {
        if (info.weapon.type == PISTOL) {
            this->player.weapon.sound = SHOT_PISTOL;
        } else if (info.weapon.type == RIFLE) {
            this->player.weapon.sound = SHOT_RIFLE;
        } else if (info.weapon.type == SHOTGUN) {
            this->player.weapon.sound = SHOT_SHOTGUN;
        } else if (info.weapon.type == SNIPER) {
            this->player.weapon.sound = SHOT_SNIPER;
        } else if (info.weapon.type == KNIFE) {
            this->player.weapon.sound = KNIFE_HIT;
        }
    }
    this->player.degrees = info.degrees;
    this->player.pos = info.pos;
    this->player.size = info.size;
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