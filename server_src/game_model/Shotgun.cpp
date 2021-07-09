#include "Shotgun.h"

Shotgun::Shotgun(World *world, GameConfig &config):Weapon(world, config, SHOTGUN){}


void Shotgun::toggle(){
    for (int i = 0; i < config.at("bullets"); i++){
        shootBullet();
    }
}
