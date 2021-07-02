#include "Weapon.h"

Weapon::Weapon(Player *owner, World *world)
:owner(owner), world(world), damage(20){}

void Weapon::toggle(){
    Ray ray;
    std::array<float, 2> pos = owner->getPosition();
    ray.x = pos[0];
    ray.y = pos[1];
    ray.angle = owner->getAngle();
    Hittable *hit = nullptr;
    float distance = 0;

    if (world->rayCast(ray, hit, distance)){
        float actual_damage = calculateDamage(distance);
        hit->recvDamage(actual_damage);
    }
}

float Weapon::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}

void Weapon::changeOwner(Player *newOwner){
    owner = newOwner;
}

World *Weapon::getWorld(){
    return world;
}
