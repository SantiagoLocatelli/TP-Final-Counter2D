#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 100

GameManager::GameManager(){}


void updateBullet(BulletInfo& bullet, Bullet prot) {
    bullet.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    bullet.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    
    int distance = Math::ruleOfThree(prot.distance, 1, PIXELS_PER_METER);
    bullet.dst.x = Math::cosOppHyp(prot.angle, distance) + bullet.pos.x;
    bullet.dst.y = Math::senoOppHyp(prot.angle, distance) + bullet.pos.y;
}

void updateDrop(DropInfo& drop, ProtDrop prot){
    drop.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    drop.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    drop.type = prot.type;
    drop.size.w = PIXELS_PER_METER/2;
    drop.size.h = PIXELS_PER_METER/2;
}

void updatePlayer(PlayerInfo& player, ProtPlayer prot) {
    player.dead = prot.dead;
    player.degrees = Math::radiansToDegrees(prot.angle);
    player.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    player.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    player.weapon = prot.weapon;
    player.size.w = PIXELS_PER_METER;
    player.size.h = PIXELS_PER_METER;
    // printf("pj x: %i\n", player.pos.x);
    // printf("pj y: %i\n", player.pos.y);
}

void updateBox(BoxInfo& box, ProtBox prot){
    box.pos.x = Math::ruleOfThree(prot.x, 1.0, PIXELS_PER_METER);
    box.pos.y = Math::ruleOfThree(prot.y, 1.0, PIXELS_PER_METER);
    box.size.w = PIXELS_PER_METER;
    box.size.h = PIXELS_PER_METER;
}

void GameManager::updatedLevel(const ModelInfo& model, LevelInfo& level){

    level.players.clear();
    level.drops.clear();
    level.bullets.clear();

    // Si no esta muerto se actualiza con el you, sino con el primero
    // que se encuentre que este vivo.
    level.mainPlayer.dead = model.you.dead;
    if (!level.mainPlayer.dead) {
        level.mainPlayer.health = model.you.health;
        level.mainPlayer.ammo = model.you.ammo;
        updatePlayer(level.mainPlayer, model.you);
        // printf("main pj x: %i\n", level.mainPlayer.pos.x);
        // printf(" mian pj y: %i\n\n", level.mainPlayer.pos.y);
    } else {
        auto it = model.players.begin();
        auto end = model.players.end();
        while (it != end && it->dead) {
            it++;
        }
        if (it != end) updatePlayer(level.mainPlayer, *it);
    }

    for (auto it = model.players.begin(); it != model.players.end(); it++){
        PlayerInfo player;
        updatePlayer(player, *it);
        level.players.push_back(player);
    }

    for (auto it = model.bullets.begin(); it != model.bullets.end(); it++){
        BulletInfo bullet;
        updateBullet(bullet, *it);
        level.bullets.push_back(bullet);
    }

    for (auto it = model.drops.begin(); it != model.drops.end(); it++) {
        DropInfo drop;
        updateDrop(drop, *it);
        level.drops.push_back(drop);
    }
}


void GameManager::initializeLevel(const MapInfo& map, const ModelInfo& model, LevelInfo& level){
    
    level.width = map.length*PIXELS_PER_METER;
    level.height = map.height*PIXELS_PER_METER;

    BoxInfo box;
    for (ProtBox prot : map.boxes) {
        updateBox(box, prot);
        level.boxes.emplace_back(box);
    }

    updatedLevel(model, level);
}
