#include "Weapon.h"
#include <cstdlib>

Weapon::Weapon(World *world, float maxDamage, float minDamage, float spread, float damageFalloff, WeaponType type):owner(nullptr), world(world), maxDamage(maxDamage), minDamage(minDamage), spread(spread), damageFalloff(damageFalloff), type(type){}


void Weapon::changeOwner(Player *newOwner){
    owner = newOwner;
}

World *Weapon::getWorld(){
    return world;
}

void Weapon::shootBullet(){
    Ray ray;

    //Le agrego un desvio a la bala
    float r = ((float) rand()) / (float) RAND_MAX;
    float spread = (2*r-1)*(this->spread);
    std::array<float, 2> pos = owner->getPosition();
    ray.x = pos[0];
    ray.y = pos[1];
    ray.angle = owner->getAngle() + spread;
    Hittable *hit = nullptr;

    if (world->rayCast(ray, hit)){
        float actual_damage = calculateDamage(ray.distance);
        hit->recvDamage(actual_damage);
        world->addBullet(ray);
    }
}

WeaponType Weapon::getType(){
    return type;
}

void Weapon::toggle(){
    shootBullet();
}

float Weapon::calculateDamage(float distance){
    //Calculo el daño entre el min y max
    float r = ((float) rand()) / (float) RAND_MAX;
    float damage = minDamage + (r * (maxDamage - minDamage));
    //El daño disminuye con la distancia
    damage *= 1/(distance*damageFalloff+1);

    return damage;
}

