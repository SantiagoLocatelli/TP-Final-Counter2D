#include "Weapon.h"


Weapon::Weapon(SdlTexture& weapon, SdlTexture& anim, Size size):
    weapon(weapon), anim(anim){
}


void Weapon::render(Coordinate dst, Size size, float degrees, bool animated){
    this->weapon.render(dst.x, dst.y, size.w, size.h, NULL, degrees + 90.0);
    
    if (animated) {
        this->anim.render(dst.x, dst.y, size.w, size.h, NULL, degrees + 90.0);
    } 
}

Weapon& Weapon::operator=(const Weapon& other){
    this->weapon = other.weapon;
    this->anim = other.anim;
    return *this;
}
Weapon::Weapon(const Weapon& other):weapon(other.weapon), anim(other.anim){}

Weapon& Weapon::operator=(Weapon&& other){
    this->weapon = other.weapon;
    this->anim = other.anim;
    return *this;
}

Weapon::Weapon(Weapon&& other):weapon(other.weapon), anim(other.anim){}