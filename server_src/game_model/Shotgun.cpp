#include "Shotgun.h"

Shotgun::Shotgun(World *world, GameConfig &config):Weapon(world, config, SHOTGUN, PRIMARY){
    bullets = this->config.getWeapon(SHOTGUN, "capacity");
}


void Shotgun::toggle(){
    toggled = !toggled;
    if (toggled && bullets > 0 && shootTime == 0){
        for (int i = 0; i < config.getWeapon(SHOTGUN, "bullets"); i++){
            shootBullet();
        }
        shootTime = config.getWeapon(SHOTGUN, "speed");
        bullets--;
    }
}
