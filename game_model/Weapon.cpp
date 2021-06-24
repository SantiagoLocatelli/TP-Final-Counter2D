#include "Weapon.h"

Weapon::Weapon(Player &owner, World &world)
:owner(owner), world(world), damage(20){}

void Weapon::activate(float angle){
    std::array<float, 2> pos = owner.getPosition();
    Player *hit_player = nullptr;
    float distance = 0;

    if (world.rayCast(pos[0], pos[1], angle, hit_player, distance)){
        float actual_damage = calculateDamage(distance);
        hit_player->recvDamage(actual_damage);
    }
}

float Weapon::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}

