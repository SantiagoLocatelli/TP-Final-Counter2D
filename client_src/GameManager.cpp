#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 80

const struct Size SIZE_SMALL_GUN = {16, 32};
const struct Size SIZE_BIG_GUN = {20, 60};

GameManager::GameManager(){}

void translatePosition(Coordinate& coord, Position pos){

    coord.x = Math::ruleOfThree(pos.x, 1.0, PIXELS_PER_METER);
    coord.y = Math::ruleOfThree(pos.y, 1.0, PIXELS_PER_METER);
}

void updateBullet(BulletInfo& bullet, Bullet prot) {
    translatePosition(bullet.pos, prot.pos);
    bullet.pos.x += Math::cosOppHyp(prot.angle, PIXELS_PER_METER/2);
    bullet.pos.y += Math::senoOppHyp(prot.angle, PIXELS_PER_METER/2);
    
    int distance = Math::ruleOfThree(prot.distance, 1, PIXELS_PER_METER) + 5;
    bullet.dst.x = Math::cosOppHyp(prot.angle, distance) + bullet.pos.x;
    bullet.dst.y = Math::senoOppHyp(prot.angle, distance) + bullet.pos.y;
}

void updateDrop(DropInfo& drop, ProtDrop prot){
    translatePosition(drop.pos, prot.pos);
    drop.type = prot.type;
    drop.size.w = PIXELS_PER_METER;
    drop.size.h = PIXELS_PER_METER;
}

void updateWeapon(WeaponInfo& weapon, ProtPlayer prot, Coordinate player) {
    weapon.type = prot.weapons[prot.currentSlot];

    // SMALL GUN    
    if (weapon.type == KNIFE || weapon.type == PISTOL || weapon.type == BOMB) {
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
}


void updatePlayer(PlayerInfo& player, ProtPlayer prot) {

    player.dead = prot.dead;
    if (!prot.dead) {
        player.weapons = prot.weapons;
        player.currentSlot = prot.currentSlot;
        translatePosition(player.pos, prot.pos);
        player.degrees = Math::radiansToDegrees(prot.angle);
        player.size.w = PIXELS_PER_METER;
        player.size.h = PIXELS_PER_METER;
        player.shooting = prot.shot;
        player.team = prot.team;
        updateWeapon(player.weapon, prot, player.pos);
    }
}


void updateBomb(BombInfo& bomb, ProtBomb prot) {
    if (prot.planted) {
        translatePosition(bomb.pos, {prot.x, prot.y});
        bomb.time = prot.timeRemaining;
        bomb.defused = prot.defused; 
    }
    bomb.planted = prot.planted;
}


void GameManager::updatedLevel(LevelInfo& level, const ModelInfo& model){

    // Si no esta muerto se actualiza con el you, sino con el primero
    // que se encuentre que este vivo.
    level.mainPlayer.dead = model.you.dead;

    if (!level.mainPlayer.dead) {
        level.mainPlayer.ammo = model.you.ammo;

        if (level.mainPlayer.health > model.you.health) {
            level.mainPlayer.damaged = true;
        } else {
            level.mainPlayer.damaged = false;
        }
        level.mainPlayer.health = model.you.health;
        updatePlayer(level.mainPlayer, model.you);

    } else {
        auto it = model.players.begin();
        auto end = model.players.end();
        while (it != end && it->dead && level.mainPlayer.team != it->team) {
            it++;
        }
        if (it != end) updatePlayer(level.mainPlayer, *it);
    }

    auto player = level.players.begin();
    for (auto prot = model.players.begin(); prot != model.players.end(); prot++){
        updatePlayer(*player, *prot);
        player++;
    }

    level.bullets.clear();
    for (auto it = model.bullets.begin(); it != model.bullets.end(); it++){
        BulletInfo bullet;
        updateBullet(bullet, *it);
        level.bullets.push_back(bullet);
    }

    level.drops.clear();
    for (auto it = model.drops.begin(); it != model.drops.end(); it++) {
        DropInfo drop;
        updateDrop(drop, *it);
        level.drops.push_back(drop);
    }

    updateBomb(level.bomb, model.bomb);
}

void translateRect(BoxInfo& box, RectArea rect){
    box.pos.x = Math::ruleOfThree(rect.x, 1.0, PIXELS_PER_METER);
    box.pos.y = Math::ruleOfThree(rect.y, 1.0, PIXELS_PER_METER);
    box.size.w = Math::ruleOfThree(rect.width, 1.0, PIXELS_PER_METER);
    box.size.h = Math::ruleOfThree(rect.height, 1.0, PIXELS_PER_METER);
}


void GameManager::initializeLevel(LevelInfo& level, const MapInfo& map, const ModelInfo& model){
    
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

    level.mainPlayer.damaged = false;
    level.mainPlayer.health = model.you.health;
    level.mainPlayer.ammo = model.you.ammo;
    level.mainPlayer.weapons = model.you.weapons;
    level.mainPlayer.currentSlot = model.you.currentSlot;
    updatePlayer(level.mainPlayer, model.you);

    updatedLevel(level, model);
}
