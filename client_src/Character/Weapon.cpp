#include "Weapon.h"


Weapon::Weapon(SdlTexture& weapon, SdlTexture& anim, Size size):
    weapon(weapon), anim(anim){
    this->info.pos = {0,0};
    this->info.size = size;
    this->info.posAnim = {0, 0};
    this->info.type = KNIFE;
}


void Weapon::render(Coordenada cam, float degrees, bool animated){
    this->weapon.render(this->info.pos.x - this->info.size.w/2 - cam.x, this->info.pos.y - this->info.size.h/2 - cam.y, this->info.size.w, this->info.size.h, NULL, degrees + 90.0);
    
    if (animated) {
        this->anim.render(this->info.pos.x - this->info.size.w/2 - cam.x, this->info.pos.y - this->info.size.h/2 - cam.y, this->info.size.w, this->info.size.h,NULL, degrees);
    } 
}

void Weapon::update(WeaponInfo info){
    this->info.pos = info.pos;
    this->info.posAnim = info.posAnim;
    this->info.size = info.size;
    this->info.type = info.type;
}


Weapon& Weapon::operator=(const Weapon& other){
    this->info = other.info;
    this->weapon = other.weapon;
    this->anim = other.anim;
    return *this;
}
Weapon::Weapon(const Weapon& other):weapon(other.weapon), anim(other.anim){
    this->info = other.info;
}

// Weapon& Weapon::operator=(Weapon&& other){
//     this->info = other.info;
//     this->weapon = other.weapon;
//     this->anim = other.anim;
//     this->soundEffect = other.soundEffect;
//     return *this;
// }
// Weapon::Weapon(Weapon&& other):weapon(other.weapon), anim(other.anim), soundEffect(other.soundEffect){
//     this->info = other.info;
// }