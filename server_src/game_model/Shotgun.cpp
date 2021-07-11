#include "Shotgun.h"

Shotgun::Shotgun(World *world, GameConfig &config):Weapon(world, config, SHOTGUN, PRIMARY){
    bullets = this->config.at("capacity");
}


void Shotgun::toggle(){
    toggled = !toggled;
    if (toggled && bullets > 0 && shootTime == 0){
        for (int i = 0; i < config.at("bullets"); i++){
            shootBullet();
        }
        shootTime = config.at("speed");
        bullets--;
    }
}
