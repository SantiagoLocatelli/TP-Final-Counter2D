#include "GodGun.h"

GodGun::GodGun(World *world)
:Weapon(world, GOD_GUN_DAMAGE){}


void GodGun::toggle(){
    shootBullet(0);
}

float GodGun::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}
