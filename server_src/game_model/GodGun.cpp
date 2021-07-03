#include "GodGun.h"

GodGun::GodGun(Player *owner, World *world)
:Weapon(owner, world, GOD_GUN_DAMAGE){}


void GodGun::toggle(){
    shootBullet(0);
}

float GodGun::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}
