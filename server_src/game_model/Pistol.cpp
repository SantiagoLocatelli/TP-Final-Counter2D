#include "Pistol.h"

Pistol::Pistol(World *world, GameConfig &config):Weapon(world, config, PISTOL){
    reload();
}
