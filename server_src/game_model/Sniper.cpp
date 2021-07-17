#include "Sniper.h"

Sniper::Sniper(World *world, GameConfig &config):Weapon(world, config, SNIPER, PRIMARY){
    bullets = this->config.getWeapon(SNIPER, "capacity");
}
