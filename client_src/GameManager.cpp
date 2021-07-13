#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 80

const struct Size SIZE_SMALL_GUN = {16, 32};
const struct Size SIZE_BIG_GUN = {20, 60};

GameManager::GameManager(){}


void updateBullet(BulletInfo& bullet, Bullet prot) {
    bullet.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER) + Math::cosOppHyp(prot.angle, PIXELS_PER_METER/2);
    bullet.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER) + Math::senoOppHyp(prot.angle, PIXELS_PER_METER/2);
    
    int distance = Math::ruleOfThree(prot.distance, 1, PIXELS_PER_METER) + 5;
    bullet.dst.x = Math::cosOppHyp(prot.angle, distance) + bullet.pos.x;
    bullet.dst.y = Math::senoOppHyp(prot.angle, distance) + bullet.pos.y;
}

void updateDrop(DropInfo& drop, ProtDrop prot){
    drop.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    drop.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    drop.type = prot.type;
    drop.size.w = PIXELS_PER_METER;
    drop.size.h = PIXELS_PER_METER;
}

void updateWeapon(WeaponInfo& weapon, ProtPlayer prot, Coordinate player) {
    weapon.type = prot.weapon;

    // SMALL GUN    
    if (weapon.type == KNIFE || weapon.type == PISTOL) {
        weapon.pos.x = Math::cosOppHyp(prot.angle, ((PIXELS_PER_METER-9)/2)) + player.x;
        weapon.pos.y = Math::senoOppHyp(prot.angle, ((PIXELS_PER_METER-9)/2)) + player.y;

        weapon.size = SIZE_SMALL_GUN;
    } else if (weapon.type == RIFLE || weapon.type == SNIPER || weapon.type == SHOTGUN) {
        // BIG GUN
        weapon.pos.x = Math::cosOppHyp(prot.angle, ((PIXELS_PER_METER-50)/2)) + player.x;
        weapon.pos.y = Math::senoOppHyp(prot.angle, ((PIXELS_PER_METER-50)/2)) + player.y;

        weapon.size = SIZE_BIG_GUN;
    }

    weapon.posAnim.x = Math::cosOppHyp(prot.angle, ((PIXELS_PER_METER+9)/2)) + player.x;
    weapon.posAnim.y = Math::senoOppHyp(prot.angle, ((PIXELS_PER_METER+9)/2)) + player.y;

    // if (prot.shot) {
    //     if (prot.weapon == PISTOL) {
    //         weapon.sound = SHOT_PISTOL;
    //     } else if (prot.weapon == RIFLE) {
    //         weapon.sound = SHOT_RIFLE;
    //     } else if (prot.weapon == SHOTGUN) {
    //         weapon.sound = SHOT_SHOTGUN;
    //     } else if (prot.weapon == SNIPER) {
    //         weapon.sound = SHOT_SHOTGUN;
    //     } else if (prot.weapon == KNIFE) {
    //         weapon.sound = KNIFE_HIT;
    //     }
    // }

}


bool equalCoords(Coordinate coord1, Coordinate coord2){
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

void updatePlayer(PlayerInfo& player, ProtPlayer prot) {
    player.sounds.clear();

    Coordinate newPos;
    newPos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    newPos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    if(!equalCoords(newPos, player.pos)){
        player.sounds.push_back(STEP);
    }
    player.pos = newPos;

    if (!player.dead && prot.dead) {
        player.sounds.push_back(DYING);
    }
    player.dead = prot.dead;

    // FALTA AGREGAR CUANDO DROPEA Y CUANDO PICK UP

    player.degrees = Math::radiansToDegrees(prot.angle);
    player.size.w = PIXELS_PER_METER;
    player.size.h = PIXELS_PER_METER;
    player.shooting = prot.shot;
    player.team = prot.team;
    updateWeapon(player.weapon, prot, player.pos);
}


LevelInfo GameManager::updatedLevel(const ModelInfo& model){

    level.drops.clear();
    level.bullets.clear();

    // Si no esta muerto se actualiza con el you, sino con el primero
    // que se encuentre que este vivo.
    level.mainPlayer.dead = model.you.dead;
    if (!level.mainPlayer.dead) {
        level.mainPlayer.health = model.you.health;
        level.mainPlayer.ammo = model.you.ammo;
        updatePlayer(level.mainPlayer, model.you);

    } else {
        auto it = model.players.begin();
        auto end = model.players.end();
        while (it != end && it->dead) {
            it++;
        }
        if (it != end) updatePlayer(level.mainPlayer, *it);
    }

    auto player = this->level.players.begin();
    for (auto prot = model.players.begin(); prot != model.players.end(); prot++){
        updatePlayer(*player, *prot);
        player++;
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

    return level;
}

void translateRect(BoxInfo& box, RectArea rect){
    box.pos.x = Math::ruleOfThree(rect.x, 1.0, PIXELS_PER_METER);
    box.pos.y = Math::ruleOfThree(rect.y, 1.0, PIXELS_PER_METER);
    box.size.w = Math::ruleOfThree(rect.width, 1.0, PIXELS_PER_METER);
    box.size.h = Math::ruleOfThree(rect.height, 1.0, PIXELS_PER_METER);
}


LevelInfo GameManager::initializeLevel(const MapInfo& map, const ModelInfo& model){
    
    level.size.w = map.length*PIXELS_PER_METER;
    level.size.h = map.height*PIXELS_PER_METER;

    BoxInfo box;
    for (auto it = map.bombSites.begin(); it != map.bombSites.end(); it++) {
        translateRect(box, *it);
        level.bombSites.push_back(box);
    }

    for (auto it = map.spawnSites.begin(); it != map.spawnSites.end(); it++) {
        translateRect(box, *it);
        level.spawnSites.push_back(box);
    }


    TileInfo tile;
    tile.size.w = PIXELS_PER_METER;
    tile.size.h = PIXELS_PER_METER;

    int max = (int)map.tiles.size();
    for(int i = 0; i < max; i++){
        tile.id = map.tiles[i];
        tile.pos.x = (i%map.length)*PIXELS_PER_METER; 
        tile.pos.y = (i/map.height)*PIXELS_PER_METER; 
        level.tiles.push_back(tile);
    }

    for (auto it = model.players.begin(); it != model.players.end(); it++){
        PlayerInfo player;
        updatePlayer(player, *it);
        level.players.push_back(player);
    }

    return updatedLevel(model);
}
