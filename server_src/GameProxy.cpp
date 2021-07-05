#include "GameProxy.h"
#include "WorldParser.h"
#include "game_model/GodGun.h"
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

    world->addDrop(new GodGun(world), 2.5f, 2.5f);
}

MapInfo GameProxy::getMapInfo(){
    return mapInfo;
}

CompleteModelInfo GameProxy::getModelInfo(){
    CompleteModelInfo info;
    std::array<float, 2> pos;
    std::vector<Player> &players = world->getPlayers();
    for (size_t i = 0; i < players.size(); i++){
            You p;
            p.dead = players[i].isDead();
            if (!p.dead){
                pos = players[i].getPosition();
                p.pos.x = pos[0];
                p.pos.y = pos[1];
                p.angle = players[i].getAngle();
                p.health = players[i].getHealth();
                p.ammo = 0;
            }
            info.players.push_back(p);
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
        d.type = GOD_GUN; //TODO: Agregar forma de que las weapon me digan su tipo
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
    //TODO: Cambiar esto, lo puse para probar.
    for (const Player &p: world->getPlayers()){
        if (p.isDead()){
            return true;
        }
    }

    return false;
}

GameProxy::~GameProxy(){
    delete world;
}

void GameProxy::clearFrameEvents(){
    world->clearBullets();
}
