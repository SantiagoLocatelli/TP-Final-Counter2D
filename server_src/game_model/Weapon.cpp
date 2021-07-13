#include "Weapon.h"
#include <cstdlib>

Weapon::Weapon(World *world, GameConfig &config, WeaponType type, WeaponSlot slot):owner(nullptr), world(world), type(type), slot(slot), config(config.getWeapon(type)), bullets(0), reloadTime(0), shootTime(0),toggled(false){}


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
    float spread = (2*r-1)*(config.at("spread"));
    std::array<float, 2> pos = owner->getPosition();
    ray.x = pos[0];
    ray.y = pos[1];
    ray.angle = owner->getAngle() + spread;
    ray.distance = config.at("maxRange");
    Hittable *hit = nullptr;

    float distance = world->rayCast(ray, hit);
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
        shootTime = config.at("speed");
        bullets--;
    }
}

int Weapon::getPrice(){
    return config.at("price");
}

float Weapon::calculateDamage(float distance){
    //Calculo el daño entre el min y max
    float r = ((float) rand()) / (float) RAND_MAX;
    float damage = config.at("minDamage") + (r * (config.at("maxDamage") - config.at("minDamage")));
    //El daño disminuye con la distancia
    damage *= 1/(distance*config.at("falloff")+1); //TODO: Cambiar a una caida lineal de daño

    return damage;
}

void Weapon::reload(){
    if (reloadTime == 0){
        reloadTime = config.at("reloadTime");
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
            bullets = config.at("capacity");
            reloadTime = 0;
        }
    }
}
