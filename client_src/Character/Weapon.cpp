#include "Weapon.h"


Weapon::Weapon(SdlTexture weapon, int width, int heigth):
    weapon(std::move(weapon)), width(width), heigth(heigth){}


void Weapon::render(int posX, int posY, float degrees){
    this->weapon.render(posX, posY, this->width, this->heigth, degrees);
}

void Weapon::update(){

}



// Weapon& Weapon::operator=(Weapon&& other){
//     this->arma_actual = other.arma_actual;
//     this->weapons = other.weapons;
//     return *this;
// }

// Weapon::Weapon(Weapon&& other): weapons(other.weapons){
//     this->arma_actual = other.arma_actual;
// }