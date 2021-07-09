#include "Shotgun.h"

Shotgun::Shotgun(World *world):Weapon(world, SHOTGUN_MAX_DAMAGE, SHOTGUN_MIN_DAMAGE, SHOTGUN_SPREAD, SHOTGUN_FALLOFF, SHOTGUN){}


void Shotgun::toggle(){
    for (int i = 0; i < SHOTGUN_BULLETS; i++){
        shootBullet();
    }
}
