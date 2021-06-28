#include "GameProxy.h"
#include "WorldParser.h"
#include <utility>

GameProxy::GameProxy(const std::string &yaml_path){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);

    world = new World(mapInfo.length, mapInfo.height);

    mapInfo.boxes = std::move(parser.get_boxes());

    for (Box b: mapInfo.boxes){
        world->addBox(b.x, b.y);
    }
}

MapInfo GameProxy::getMapInfo(){
    return mapInfo;
}

CompleteModelInfo GameProxy::getModelInfo(){
    CompleteModelInfo info;
    std::array<float, 2> pos;
    for (int i = 0; i < players.size(); i++){
            You p;
            pos = players[i]->getPosition();
            p.x = pos[0];
            p.y = pos[1];
            p.angle = players[i]->getAngle();
            p.health = players[i]->getHealth();
            p.ammo = 0;
            info.players.push_back(p);
    }

    info.game_ended = ended();
}

void GameProxy::step(){
    world->step();
}

int GameProxy::createPlayer(int team){
    players.push_back(&world->createPlayer(team+1, team+1));
    return (players.size()-1);
}

void GameProxy::toggleMovement(int id, Direction direction){
    players[id]->toggleMovement(direction);
}

void GameProxy::rotate(int id, float angle){
    players[id]->rotate(angle);
}

void GameProxy::activateWeapon(int id){
    players[id]->activateWeapon();
}

bool GameProxy::ended(){
    //TODO: Cambiar esto, lo puse para probar.
    for (Player *p: players){
        if (p->isDead()){
            return true;
        }
    }

    return false;
}

GameProxy::~GameProxy(){
    delete world;
}
