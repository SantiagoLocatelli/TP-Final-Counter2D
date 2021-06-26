#include "GameProxy.h"
#include "WorldParser.h"
#include <utility>

GameProxy::GameProxy(const std::string &yaml_path){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);

    world = new World(mapInfo.length, mapInfo.height);
    parser.fill_world(world);

    mapInfo.boxes = std::move(parser.get_boxes());
}

MapInfo GameProxy::getMapInfo(){
    return mapInfo;
}

ModelInfo GameProxy::getModelInfo(int id){
    ModelInfo info;
    std::array<float, 2> pos = players[id].getPosition();
    info.you.x = pos[0];
    info.you.y = pos[1];
    info.you.angle = players[id].getAngle();
    info.you.health = players[id].getHealth();
    info.you.ammo = 0;

    for (int i = 0; i < players.size(); i++){
        if (i != id){
            Prot_Player p;
            pos = players[i].getPosition();
            p.x = pos[0];
            p.y = pos[1];
            p.angle = players[i].getAngle();
        }
    }
}

void GameProxy::step(){
    world->step();
}

int GameProxy::createPlayer(char team){
    players.push_back(world->createPlayer(team));
    return (players.size()-1);
}

void GameProxy::toggleMovement(int id, Direction direction){
    players[id].toggleMovement(direction);
}

void GameProxy::rotate(int id, float angle){
    players[id].rotate(angle);
}

void GameProxy::activateWeapon(int id){
    players[id].activateWeapon();
}

GameProxy::~GameProxy(){
    delete world;
}
