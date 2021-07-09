#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 100

const struct Size SIZE_SMALL_GUN = {16, 32};
const struct Size SIZE_BIG_GUN = {30, 60};

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

void updateWeapon(WeaponInfo& weapon, ProtPlayer prot, Coordenada player) {
    // weapon.type = prot.weapon;
    weapon.type = PISTOL;

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

    weapon.posAnim.x = Math::cosOppHyp(prot.angle, ((PIXELS_PER_METER-9)/2)) + player.x;
    weapon.posAnim.y = Math::senoOppHyp(prot.angle, ((PIXELS_PER_METER-9)/2)) + player.y;
}

void updatePlayer(PlayerInfo& player, ProtPlayer prot) {
    player.dead = prot.dead;
    player.degrees = Math::radiansToDegrees(prot.angle);
    player.pos.x = Math::ruleOfThree(prot.pos.x, 1.0, PIXELS_PER_METER);
    player.pos.y = Math::ruleOfThree(prot.pos.y, 1.0, PIXELS_PER_METER);
    player.size.w = PIXELS_PER_METER;
    player.size.h = PIXELS_PER_METER;
    player.shooting = prot.shooting;

    updateWeapon(player.weapon, prot, player.pos);
}

// void updateBox(BoxInfo& box, ProtBox prot){
//     box.pos.x = Math::ruleOfThree(prot.x, 1.0, PIXELS_PER_METER);
//     box.pos.y = Math::ruleOfThree(prot.y, 1.0, PIXELS_PER_METER);
//     box.size.w = PIXELS_PER_METER;
//     box.size.h = PIXELS_PER_METER;
// }

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

void translateRect(BoxInfo& box, RectArea rect){
    box.pos.x = Math::ruleOfThree(rect.x, 1.0, PIXELS_PER_METER);
    box.pos.y = Math::ruleOfThree(rect.y, 1.0, PIXELS_PER_METER);
    box.size.w = Math::ruleOfThree(rect.width, 1.0, PIXELS_PER_METER);
    box.size.h = Math::ruleOfThree(rect.height, 1.0, PIXELS_PER_METER);
}


void GameManager::initializeLevel(const MapInfo& map, const ModelInfo& model, LevelInfo& level){
    
    level.width = map.length*PIXELS_PER_METER;
    level.height = map.height*PIXELS_PER_METER;

    BoxInfo box;
    for (auto it = map.bombSites.begin(); it != map.bombSites.end(); it++) {
        translateRect(box, *it);
        level.bombSites.push_back(box);
    }

    for (auto it = map.spawnSites.begin(); it != map.spawnSites.end(); it++) {
        translateRect(box, *it);
        level.spawnSites.push_back(box);
    }


    int maxRow = map.height;
    int maxCol = map.length;

    TileInfo tile;
    tile.size.w = PIXELS_PER_METER;
    tile.size.h = PIXELS_PER_METER;

    for(int i = 0; i < map.tiles.size(); i++){
        tile.id = map.tiles[i];
        tile.pos.x = (i%map.length)*PIXELS_PER_METER; 
        tile.pos.y = (i/map.height)*PIXELS_PER_METER; 
        level.tiles.push_back(tile);
    }

    updatedLevel(model, level);
}
