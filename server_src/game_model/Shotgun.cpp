#include "Shotgun.h"

Shotgun::Shotgun(World *world, GameConfig &config):Weapon(world, config, SHOTGUN){
    reload();
}


void Shotgun::toggle(){
    if (bullets > 0){
        for (int i = 0; i < config.at("bullets"); i++){
            shootBullet();
        }
        bullets--;
    }
}
