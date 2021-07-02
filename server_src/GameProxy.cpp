#include "GameProxy.h"
#include "WorldParser.h"
#include <utility>

#include <list>
#include <map>

GameProxy::GameProxy(const std::string &yaml_path){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);

    world = new World(mapInfo.length, mapInfo.height);

    mapInfo.boxes = std::move(parser.get_boxes());

    for (Prot_Box b: mapInfo.boxes){
        world->addBox(b.x, b.y);
    }
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
                p.x = pos[0];
                p.y = pos[1];
                p.angle = players[i].getAngle();
                p.health = players[i].getHealth();
                p.ammo = 0;
            }
            info.players.push_back(p);
    }

    for (Ray &ray: world->getBullets()){
        Bullet b;
        b.start_x = ray.x;
        b.start_y = ray.y;
        b.angle = ray.angle;
        b.distance = ray.distance;
        info.bullets.push_back(b);
    }

    info.game_ended = ended();

    return info;
}

void GameProxy::step(){
    world->step();
}

void GameProxy::createPlayer(int team){
    world->createPlayer(team+1, team+1);
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
    // for (const Player &p: world->getPlayers()){
    //     if (p.isDead()){
    //         return true;
    //     }
    // }

    return false;
}

GameProxy::~GameProxy(){
    delete world;
}
