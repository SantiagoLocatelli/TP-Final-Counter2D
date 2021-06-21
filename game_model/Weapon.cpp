#include "Weapon.h"

Weapon::Weapon(Player &owner, World &world)
:owner(owner), world(world), damage(20){}

void Weapon::activate(float angle){
}
