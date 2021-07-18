#include "GameManager.h"
#include "gameMath.h"

#define METERS_TO_SHOW 10
#define SIZE_SMALL_GUN 0
#define SIZE_BIG_GUN 1


GameManager::GameManager(Size windowSize){
    this->pixelsPerMeter.w = windowSize.w / METERS_TO_SHOW;
    this->pixelsPerMeter.h = windowSize.h / METERS_TO_SHOW;

    this->sizeWeapons[SIZE_SMALL_GUN] = {this->pixelsPerMeter.w/5, 2*this->pixelsPerMeter.h/5};
    this->sizeWeapons[SIZE_BIG_GUN] = {this->pixelsPerMeter.w/4, 3*this->pixelsPerMeter.h/4};
}

void GameManager::translatePosition(Coordinate& coord, Position pos){

    coord.x = Math::metersToPixels(pos.x, 1.0, this->pixelsPerMeter.w);
    coord.y = Math::metersToPixels(pos.y, 1.0, this->pixelsPerMeter.h);
}

void GameManager::updateBullet(BulletInfo& bullet, Bullet prot) {
    translatePosition(bullet.pos, prot.pos);

    // es para que la bullet salga desde el arma y no desde el centro del jugador
    bullet.pos.x += Math::cosAdHyp(prot.angle, this->pixelsPerMeter.w/2);
    bullet.pos.y += Math::senoOppHyp(prot.angle, this->pixelsPerMeter.h/2);
    
    Position distanceMeters;
    distanceMeters.x = Math::cosAdHyp(prot.angle, prot.distance);
    distanceMeters.y = Math::senoOppHyp(prot.angle, prot.distance);

    Coordinate distancePixels;
    translatePosition(distancePixels, distanceMeters);

    int distance = Math::pythagoras(distancePixels.x, distancePixels.y) + 5;
    bullet.dst.x = Math::cosAdHyp(prot.angle, distance) + bullet.pos.x;
    bullet.dst.y = Math::senoOppHyp(prot.angle, distance) + bullet.pos.y;
}

void GameManager::updateDrop(DropInfo& drop, ProtDrop prot){
    translatePosition(drop.pos, prot.pos);
    drop.type = prot.type;
    drop.size.w = this->pixelsPerMeter.w;
    drop.size.h = this->pixelsPerMeter.h;
} 

void GameManager::updateWeapon(WeaponInfo& weapon, ProtPlayer prot, Coordinate player) {
    weapon.type = prot.weapons[prot.currentSlot];

    Size phaseShift = {(int) (this->pixelsPerMeter.w*0.1),(int) (this->pixelsPerMeter.h*0.1)};

    // SMALL GUN    
    if (weapon.type == KNIFE || weapon.type == PISTOL || weapon.type == BOMB) {
        weapon.pos.x = Math::cosAdHyp(prot.angle, ((this->pixelsPerMeter.w - phaseShift.w)/2)) + player.x;
        weapon.pos.y = Math::senoOppHyp(prot.angle, ((this->pixelsPerMeter.h - phaseShift.h)/2)) + player.y;

        weapon.size = this->sizeWeapons[SIZE_SMALL_GUN];
    } else if (weapon.type == RIFLE || weapon.type == SNIPER || weapon.type == SHOTGUN) {
        // BIG GUN
        weapon.pos.x = Math::cosAdHyp(prot.angle, ((this->pixelsPerMeter.w)/4)) + player.x;
        weapon.pos.y = Math::senoOppHyp(prot.angle, ((this->pixelsPerMeter.h)/4)) + player.y;

        weapon.size = this->sizeWeapons[SIZE_BIG_GUN];
    }

    weapon.posAnim.x = Math::cosAdHyp(prot.angle, ((this->pixelsPerMeter.w + phaseShift.w)/2)) + player.x;
    weapon.posAnim.y = Math::senoOppHyp(prot.angle, ((this->pixelsPerMeter.h + phaseShift.h)/2)) + player.y;
}

void GameManager::updatePlayer(PlayerInfo& player, ProtPlayer prot) {

    player.dead = prot.dead;
    if (!prot.dead) {
        player.weapons = prot.weapons;
        player.currentSlot = prot.currentSlot;
        translatePosition(player.pos, prot.pos);
        player.degrees = Math::radiansToDegrees(prot.angle);
        player.size.w = this->pixelsPerMeter.w;
        player.size.h = this->pixelsPerMeter.h;
        player.shooting = prot.shot;
        player.team = prot.team;
        updateWeapon(player.weapon, prot, player.pos);
    }
}

void GameManager::updateBomb(BombInfo& bomb, ProtBomb prot) {
    if (prot.planted) {
        translatePosition(bomb.pos, {prot.x, prot.y});
        bomb.time = prot.timeRemaining;
        bomb.defused = prot.defused; 
    }
    bomb.planted = prot.planted;
}

void GameManager::updatedLevel(LevelInfo& level, const ModelInfo& model){

    level.state = model.state;
    level.timeRemaining = model.timeRemaining;
    // Si no esta muerto se actualiza con el you, sino con el primero
    // que se encuentre que este vivo.
    level.mainPlayer.dead = model.you.dead;

    if (!level.mainPlayer.dead) {
        level.mainPlayer.ammo = model.you.ammo;
        level.mainPlayer.money = model.you.money;
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

void GameManager::translateRect(BoxInfo& box, RectArea rect){
    translatePosition(box.pos, {rect.x,rect.y});
    box.size.w = Math::metersToPixels(rect.width, 1.0, this->pixelsPerMeter.w);
    box.size.h = Math::metersToPixels(rect.height, 1.0, this->pixelsPerMeter.h);
}

void GameManager::initializeLevel(LevelInfo& level, const MapInfo& map, const ModelInfo& model){
    
    level.size.w = map.length*this->pixelsPerMeter.w;
    level.size.h = map.height*this->pixelsPerMeter.h;

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
    tile.size.w = this->pixelsPerMeter.w;
    tile.size.h = this->pixelsPerMeter.h;

    int max = (int)map.tiles.size();
    for(int i = 0; i < max; i++){
        tile.id = map.tiles[i];
        tile.pos.x = (i%map.length)*this->pixelsPerMeter.w; 
        tile.pos.y = (i/map.length)*this->pixelsPerMeter.h; 
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
