#include "Sniper.h"

Sniper::Sniper(World *world)
:Weapon(world, SNIPER_DAMAGE, SNIPER){}


void Sniper::toggle(){
    shootBullet(0);
}

float Sniper::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}
