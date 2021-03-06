#include "Rifle.h"

Rifle::Rifle(World *world, GameConfig &config):Weapon(world, config, RIFLE, PRIMARY), burstShots(0){
    bullets = this->config.getWeapon(RIFLE, "capacity");
}

void Rifle::toggle(){
    toggled = !toggled;
    if (toggled && bullets > 0 && shootTime == 0){
        shootBullet();
        burstShots = 0;
        shootTime = config.getWeapon(RIFLE, "burstTime");
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
                    shootTime = config.getWeapon(RIFLE, "speed");
                } else {
                    shootTime = config.getWeapon(RIFLE, "burstTime");
                }
            }
        }
    }

    if (reloadTime > 0){
        reloadTime -= delta;
        if (reloadTime <= 0){
            bullets = config.getWeapon(RIFLE, "capacity");
            reloadTime = 0;
        }
    }

}
