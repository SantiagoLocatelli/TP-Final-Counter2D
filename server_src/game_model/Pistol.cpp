#include "Pistol.h"

Pistol::Pistol(World *world)
:Weapon(world, PISTOL_DAMAGE, PISTOL){}


void Pistol::toggle(){
    shootBullet(0);
}

float Pistol::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}
