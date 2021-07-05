#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 100


GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h):
    map(map), game(window_w, window_h, this->generateLevel(model)){

}


void GameManager::updateBullet(BulletInfo& bullet, Bullet prot) {
    bullet.pos.x = Math::ruleOfThree(prot.pos.x, this->map.length, this->map.length*PIXELS_PER_METER);
    bullet.pos.y = Math::ruleOfThree(prot.pos.y, this->map.height, this->map.height*PIXELS_PER_METER);
    
    int distance = Math::ruleOfThree(prot.distance, 1, PIXELS_PER_METER);
    bullet.dst.x = Math::cosOppHyp(prot.angle, distance) + bullet.pos.x;
    bullet.dst.y = Math::senoOppHyp(prot.angle, distance) + bullet.pos.y;

}

void GameManager::updateDrop(DropInfo& drop, ProtDrop prot){
    drop.pos.x = Math::ruleOfThree(prot.pos.x, this->map.length, this->map.length*PIXELS_PER_METER);
    drop.pos.y = Math::ruleOfThree(prot.pos.y, this->map.height, this->map.height*PIXELS_PER_METER);
    drop.type = prot.type;
    drop.size.w = PIXELS_PER_METER/2;
    drop.size.h = PIXELS_PER_METER/2;
}

void GameManager::updatePlayer(PlayerInfo& player, ProtPlayer prot) {
    player.dead = prot.dead;
    player.degrees = Math::radiansToDegrees(prot.angle);
    player.pos.x = Math::ruleOfThree(prot.pos.x, this->map.length, (int)(this->map.length*PIXELS_PER_METER));
    player.pos.y = Math::ruleOfThree(prot.pos.y, this->map.height, (int)(this->map.height*PIXELS_PER_METER));
    player.weapon = prot.weapon;
    player.size.w = PIXELS_PER_METER;
    player.size.h = PIXELS_PER_METER;
}

void GameManager::update(ModelInfo model){

    LevelInfo level;

    // Si esta muerto se actualiza con el you, sino con el primero
    // que se encuentre que este vivo.
    level.mainPlayer.dead = model.you.dead;
    if (!level.mainPlayer.dead) {
        level.mainPlayer.health = model.you.health;
        level.mainPlayer.ammo = model.you.ammo;
        this->updatePlayer(level.mainPlayer, model.you);
    } else {
        auto it = model.players.begin();
        auto end = model.players.end();
        while (it != end && it->dead) {
            it++;
        }
        if (it != end) this->updatePlayer(level.mainPlayer, *it);
    }

    for (auto it = model.players.begin(); it != model.players.end(); it++){
        PlayerInfo player;
        this->updatePlayer(player, *it);
        level.players.push_back(player);
    }

    for (auto it = model.bullets.begin(); it != model.bullets.end(); it++){
        BulletInfo bullet;
        this->updateBullet(bullet, *it);
        level.bullets.push_back(bullet);
    }

    for (auto it = model.drops.begin(); it != model.drops.end(); it++) {
        DropInfo drop;
        this->updateDrop(drop, *it);
        level.drops.push_back(drop);
    }

    for (auto it = this->map.boxes.begin(); it != this->map.boxes.end(); it++) {
        Coordenada box;
        box.x = Math::ruleOfThree(it->x, 1, PIXELS_PER_METER);
        box.y = Math::ruleOfThree(it->y, 1, PIXELS_PER_METER);
    }

    this->game.update(level);
}

Coordenada GameManager::getRelativePlayerPos(){this->game.mainPlayerRelativePos();}
void GameManager::setCrossHair(Coordenada pos){this->game.setCrossHair(pos);}
