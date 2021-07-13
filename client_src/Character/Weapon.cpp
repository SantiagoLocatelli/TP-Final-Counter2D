#include "Weapon.h"


Weapon::Weapon(SdlTexture& weapon, SdlTexture& anim, WeaponType type):
    weapon(weapon), anim(anim), type(type){
}


void Weapon::render(Coordinate dstWp, Coordinate dstAnim, Size size, float degrees, bool animated){
    if (animated && this->type == KNIFE) {
        this->anim.render(dstAnim.x, dstAnim.y, size.w, size.h, NULL, degrees + 90.0);
        return;
    }
    this->weapon.render(dstWp.x, dstWp.y, size.w, size.h, NULL, degrees + 90.0);
    if (animated) {
        this->anim.render(dstAnim.x, dstAnim.y, size.w, size.h, NULL, degrees + 90.0);
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