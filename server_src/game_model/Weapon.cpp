#include "Weapon.h"

Weapon::Weapon(World *world, float damage, WeaponType type)
:owner(nullptr), world(world), damage(damage), type(type){}


void Weapon::changeOwner(Player *newOwner){
    owner = newOwner;
}

World *Weapon::getWorld(){
    return world;
}

void Weapon::shootBullet(float spread){
    Ray ray;
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

