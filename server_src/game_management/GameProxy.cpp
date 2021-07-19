#include "GameProxy.h"
#include "WorldParser.h"
#include "../../common_src/Utils.h"
#include "../game_model/Bomb.h"
#include <utility>

#include <list>
#include <map>

GameProxy::GameProxy(const std::string &yaml_path, GameConfig &config): config(config){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);


    for (int t: parser.get_tiles()){
        mapInfo.tiles.push_back((uint8_t) t);
    }

    mapInfo.bombSites = parser.get_sites();
    mapInfo.spawnSites = parser.get_spawn();

    mapInfo.terrorSkin = (SkinType)config.getGame("terrorSkin");
    mapInfo.counterSkin = (SkinType)config.getGame("counterSkin");
    mapInfo.weaponPrices[0] = config.getWeapon(SNIPER, "price");
    mapInfo.weaponPrices[1] = config.getWeapon(SHOTGUN, "price");
    mapInfo.weaponPrices[2] = config.getWeapon(RIFLE, "price");

    world = new World(mapInfo, config);
    roundManager = new RoundManager(*world, config);

    for (auto b: parser.get_boxes()){
        world->addBox(b[0], b[1]);
    }
    for (ProtDrop &d: parser.get_weapons()){
        world->addStartingDrop(d);
    }
}

void GameProxy::setUpGame(){
    roundManager->resetRound();
}


MapInfo GameProxy::getMapInfo(){
    return mapInfo;
}

CompleteModelInfo GameProxy::getModelInfo(){
    CompleteModelInfo info;
    std::array<float, 2> pos;
    std::vector<Player> &players = world->getPlayers();
    for (const Player &p: players){
            You you;
            you.dead = p.isDead();
            if (!you.dead){
                pos = p.getPosition();
                you.pos.x = pos[0];
                you.pos.y = pos[1];
                you.angle = p.getAngle();
                you.health = p.getHealth();
                you.weapons = std::move(p.getWeapons());
                you.currentSlot = p.getWeaponSlot();
                you.shot = p.shot;
                you.team = p.getTeam();
                you.ammo = p.getAmmo();
                you.money = p.getMoney();
            }
            info.players.push_back(you);
    }

    for (Ray &ray: world->getBullets()){
        Bullet b;
        b.pos.x = ray.x;
        b.pos.y = ray.y;
        if (ray.angle < 0){
            b.angle = ray.angle + 6.2832; //Le sumo 2PI
        } else {
            b.angle = ray.angle; 
        }
        b.distance = ray.distance;
        info.incompleteModel.bullets.push_back(b);
    }

    for (Drop *drop : world->getDrops()){
        ProtDrop d;
        d.pos.x = drop->getPosition()[0];
        d.pos.y = drop->getPosition()[1];
        d.type = drop->getWeapon()->getType();
        info.incompleteModel.drops.push_back(d);
    }

    info.incompleteModel.game_ended = ended();
    info.incompleteModel.bomb = world->getBomb();
    info.incompleteModel.timeRemaining = roundManager->getTime();
    info.incompleteModel.state.roundState = roundManager->getRoundState();
    info.incompleteModel.state.gameState = roundManager->getGameState();
    info.incompleteModel.state.endResult = roundManager->getRoundResult();
    info.incompleteModel.state.roundScore = roundManager->getRoundScore();

    return info;
}

void GameProxy::step(float delta){
    if (roundManager->step(delta)){
        world->step(delta);
    }
}

void GameProxy::createPlayer(Team team){
    if (team == TERROR){
        world->createPlayer(team);
    } else {
        world->createPlayer(team);
    }
}

Player &GameProxy::getPlayer(int id){
    return world->getPlayers()[id];
}

bool GameProxy::ended(){
    return roundManager->getGameState();
}

GameProxy::~GameProxy(){
    delete world;
    delete roundManager;
}

void GameProxy::clearFrameEvents(){
    world->clearBullets();
    for (Player &p: world->getPlayers()){
        p.shot = false;
    }
}

RoundState GameProxy::getRoundState(){
    return roundManager->getRoundState();
}

