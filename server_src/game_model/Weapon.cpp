#include "Weapon.h"
#include <cstdlib>

Weapon::Weapon(World *world, GameConfig &config, WeaponType type, WeaponSlot slot):owner(nullptr), world(world), type(type), slot(slot), config(config), bullets(0), reloadTime(0), shootTime(0),toggled(false), rayCaster(world->b2world){}


void Weapon::changeOwner(Player *newOwner){
    owner = newOwner;
}

World *Weapon::getWorld(){
    return world;
}

void Weapon::shootBullet(){
    Ray ray;
    owner->shot = true;

    //Le agrego un desvio a la bala
    float r = ((float) rand()) / (float) RAND_MAX;
    float spread = (2*r-1)*(config.getWeapon(type, "spread"));
    std::array<float, 2> pos = owner->getPosition();
    ray.x = pos[0];
    ray.y = pos[1];
    ray.angle = owner->getAngle() + spread;
    ray.distance = config.getWeapon(type, "maxRange");
    Hittable *hit = nullptr;

    float distance = rayCaster.castRay(ray, hit);
    if (distance != -1){
        float actual_damage = calculateDamage(distance);
        hit->recvDamage(actual_damage);
        ray.distance = distance;
        world->addBullet(ray);
    }
}

WeaponType Weapon::getType(){
    return type;
}

WeaponSlot Weapon::getSlot(){
    return slot;
}

int Weapon::getAmmo(){
    return bullets;
}

void Weapon::toggle(){
    toggled = !toggled;
    if (toggled && bullets > 0 && shootTime == 0){
        shootBullet();
        shootTime = config.getWeapon(type, "speed");
        bullets--;
    }
}

int Weapon::getPrice(){
    return config.getWeapon(type, "price");
}

float Weapon::calculateDamage(float distance){
    if (distance > config.getWeapon(type, "maxRange"))
        return 0;
    //Calculo el daño entre el min y max
    float r = ((float) rand()) / (float) RAND_MAX;
    float damage = config.getWeapon(type, "minDamage") + (r * (config.getWeapon(type, "maxDamage") - config.getWeapon(type, "minDamage")));
    //El daño disminuye con la distancia
    damage -= config.getWeapon(type, "falloff")*distance;
    if (damage < 0)
        return 0;

    return damage;
}

void Weapon::reload(){
    if (reloadTime == 0){
        reloadTime = config.getWeapon(type, "reloadTime");
    }
}

void Weapon::step(float delta){
    if (shootTime > 0){
        shootTime -= delta;
        if (shootTime < 0){
            shootTime = 0;
        }
    }

    if (reloadTime > 0){
        reloadTime -= delta;
        if (reloadTime <= 0){
            bullets = config.getWeapon(type, "capacity");
            reloadTime = 0;
        }
    }
}
