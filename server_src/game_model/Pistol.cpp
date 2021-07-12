#include "Pistol.h"

Pistol::Pistol(World *world, GameConfig &config):Weapon(world, config, PISTOL, SECONDARY){
    bullets = this->config.at("capacity");
}
