#include "Rifle.h"

Rifle::Rifle(World *world, GameConfig &config):Weapon(world, config, RIFLE, PRIMARY), burstShots(0){
    bullets = this->config.at("capacity");
}

void Rifle::toggle(){
    toggled = !toggled;
    if (toggled && bullets > 0 && shootTime == 0){
        shootBullet();
        burstShots = 0;
        shootTime = config.at("burstTime");
        burstShots++;
        bullets--;
    }

}

void Rifle::step(float delta){
    if (shootTime > 0){
        shootTime -= delta;
        if (shootTime < 0){
            shootTime = 0;
            if(bullets > 0 && toggled){
                shootBullet();
                burstShots++;
                bullets--;
                if (burstShots == 3){
                    burstShots = 0;
                    shootTime = config.at("speed");
                } else {
                    shootTime = config.at("burstTime");
                }
            }
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
