#include "GameProxy.h"
#include "WorldParser.h"
#include "game_model/Sniper.h"
#include <utility>

#include <list>
#include <map>

GameProxy::GameProxy(const std::string &yaml_path){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);

    world = new World(mapInfo.length, mapInfo.height);

    mapInfo.boxes = std::move(parser.get_boxes());

    for (ProtBox b: mapInfo.boxes){
        world->addBox(b.x, b.y);
    }

    world->addDrop(new Sniper(world), 5.5f, 5.5f);
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
                you.weapon = p.getWeaponType();
                you.shooting = p.isShooting();
                you.ammo = 0;
            }
            info.players.push_back(you);
    }

    for (Ray &ray: world->getBullets()){
        Bullet b;
        b.pos.x = ray.x;
        b.pos.y = ray.y;
        b.angle = ray.angle;
        b.distance = ray.distance;
        info.bullets.push_back(b);
    }

    for (Drop *drop : world->getDrops()){
        ProtDrop d;
        d.pos.x = drop->getPosition()[0];
        d.pos.y = drop->getPosition()[1];
        d.type = drop->getWeapon()->getType();
        info.drops.push_back(d);
    }

    info.game_ended = ended();

    return info;
}

void GameProxy::step(){
    world->step();
}

void GameProxy::createPlayer(){
    world->createPlayer();
}

void GameProxy::toggleMovement(int id, Direction direction){
    world->getPlayers()[id].toggleMovement(direction);
}

void GameProxy::setAngle(int id, float angle){
    world->getPlayers()[id].setAngle(angle);
}

void GameProxy::toggleWeapon(int id){
    world->getPlayers()[id].toggleWeapon();
}

bool GameProxy::ended(){
    int alive_players = 0;
    for (const Player &p: world->getPlayers()){
        if (!p.isDead()){
            alive_players++;
        }
    }

    return alive_players <= 1;
}

GameProxy::~GameProxy(){
    delete world;
}

void GameProxy::clearFrameEvents(){
    world->clearBullets();
}
