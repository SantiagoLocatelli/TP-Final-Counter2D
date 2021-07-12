#include "Bomb.h"

Bomb::Bomb(World *world, GameConfig &config):Weapon(world, config, BOMB, BOMB_SLOT), plantTime(0){}

void Bomb::toggle(){
    if (world->canPlant(owner->getPosition()[0], owner->getPosition()[1])){
        toggled = !toggled;
        if (toggled){
            plantTime = config.at("speed");
        }
    }
}

void Bomb::reload(){}

void Bomb::step(float delta){
    if (toggled){
        plantTime -= delta;
        if (plantTime <= 0){
            world->plantBomb(owner->getPosition()[0], owner->getPosition()[1]);
            owner->destroyWeapon(BOMB_SLOT);
        }
    }
}
