#include "Knife.h"
#include <set>

Knife::Knife(World *world, GameConfig &config):Weapon(world, config, KNIFE, KNIFE_SLOT){}

void Knife::toggle(){
    toggled = !toggled;
    if (toggled){
        owner->shot = true;
        std::set<Hittable*> hit;
        for (float angle = -0.4; angle <= 0.4; angle+=0.1){
            Ray ray;
            ray.x = owner->getPosition()[0];
            ray.y = owner->getPosition()[1];
            ray.angle = owner->getAngle() + angle;
            ray.distance = 1;
            Hittable *h;
            if (rayCaster.castRay(ray, h) != -1){
                hit.insert(h);
            }
        }
        for (Hittable *h: hit){
            h->recvDamage(config.getWeapon(KNIFE, "damage"));
        }
    }
}

void Knife::reload(){}
