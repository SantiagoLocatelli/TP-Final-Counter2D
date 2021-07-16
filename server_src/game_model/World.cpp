#include "World.h"
#include <utility>
#include "EntityChecker.h"
#include "../../common_src/GeneralException.h"
#include "Bomb.h"
#include "Rifle.h"
#include "Shotgun.h"
#include "Sniper.h"


World::World(MapInfo mapInfo, GameConfig &config):player_number(0), mapInfo(mapInfo), b2world(b2Vec2(0,0)), config(config){
    bomb.planted = false;
    b2world.SetContactListener(&collisionHandler);
}

void World::addBox(int grid_x, int grid_y){
    if(grid_x < 0 || grid_x > mapInfo.length || grid_y < 0 || grid_y > mapInfo.height)
        throw GeneralException("Posicicon para `addBox` fuera de límites");
    boxes.push_back(Box(b2world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f));
}

void World::createPlayer(Team team){
    players.emplace_back(std::move(Player(*this, 0, 0, config, team)));
}

std::vector<Player> &World::getPlayers(){
    return players;
}

void World::step(float delta){
    for (Player &p: players){
        if (!p.isDead()){
            p.updateVelocity();
            p.step(delta);
        }
    }

    if (bomb.planted){
        bomb.timeRemaining -= delta;
    }

    b2world.Step(delta, 10, 9);

    for (b2Body *b : bodiesToDestroy){
        //Aca elimino todos los drops
        if ((void *)b->GetFixtureList()->GetUserData().pointer != nullptr)
            delete (Drop *)b->GetFixtureList()->GetUserData().pointer;
        b2world.DestroyBody(b);
    }
    bodiesToDestroy.clear();
}

void World::addBullet(Ray ray){
    bullets.push_back(ray);
}

std::list<Ray> &World::getBullets(){
    return bullets;
}

void World::clearBullets(){
    bullets.clear();
}

void World::addDrop(Weapon *weapon, float x, float y){
    new Drop(*this, x, y, weapon);
}

std::list<Drop*> World::getDrops(){
    std::list<Drop*> drops;
    for (b2Body* b = b2world.GetBodyList(); b; b = b->GetNext()){
        b2Fixture *fixture = b->GetFixtureList();
        Drop *drop = (Drop *)fixture->GetUserData().pointer;
        if (drop != nullptr){
            //Si estoy aca es porque este b2Body era un Drop
            drops.push_back(drop);
        }
    }

    return drops;
}

void World::destroyBody(b2Body *body){
    bodiesToDestroy.push_back(body);
}

World::~World(){
    for (b2Body* b = b2world.GetBodyList(); b; b = b->GetNext()){
        b2Fixture *fixture = b->GetFixtureList();
        Drop *drop = (Drop *)fixture->GetUserData().pointer;
        if (drop != nullptr){
            //Si estoy aca es porque este b2Body era un Drop
            delete drop;
        }
    }
}

void World::plantBomb(float x, float y){
    if (!bomb.planted){
        bomb.planted = true;
        bomb.defused = false;
        bomb.x = x;
        bomb.y = y;
        bomb.timeRemaining = config.getGame().at("bombTime");
    }
}

bool World::bombExploded(){
    return bomb.planted && bomb.timeRemaining <= 0;
}

void World::defuseBomb(){
    if (bomb.planted){
        bomb.defused = true;
    }
}
bool World::bombDefused(){
    return bomb.planted && bomb.defused;
}


bool World::canPlant(float x, float y){
    if (bomb.planted)
        return false;

    for (const RectArea &site: mapInfo.bombSites){
        if (positionInArea(x, y, site)){
            return true;
        }
    }

    return false;
}

bool World::canDefuse(float x, float y){
    if (bomb.planted && !bomb.defused){
        if (b2Vec2(x-bomb.x, y-bomb.y).Length() <= config.getGame().at("bombDefuseDistance")){
            return true;
        }
    }

    return false;
}

ProtBomb World::getBomb(){
    return bomb;
}

bool World::canBuy(Player &player){
    //TODO: Esto deberia depender del roundState, no de la posición.
    return positionInArea(player.getPosition()[0], player.getPosition()[1], mapInfo.spawnSites[player.getTeam()]);
}

bool World::positionInArea(float x, float y, RectArea area){
    return (x > area.x && x < area.x+area.width && y > area.y && y < area.y+area.height);
}

void World::addStartingDrop(ProtDrop drop){
    startingDrops.push_back(drop);
}

void World::resetWorld(bool changeTeams){
    //Destruyo los drops
    for (b2Body* b = b2world.GetBodyList(); b; b = b->GetNext()){
        b2Fixture *fixture = b->GetFixtureList();
        Drop *drop = (Drop *)fixture->GetUserData().pointer;
        if (drop != nullptr){
            b2world.DestroyBody(fixture->GetBody());
            delete drop;
        }
    }

    //Reseteo la bomba
    if (bomb.planted)
        bomb.planted = false;
    addDrop(new Bomb(this, config), mapInfo.spawnSites[TERROR].x+CELL_SIZE/2, mapInfo.spawnSites[TERROR].y+CELL_SIZE/2);

    for (Player &p: players){
        Team team = p.getTeam();
        if (changeTeams)
            team = team == TERROR ? COUNTER : TERROR;
        b2Vec2 pos = getValidPosition(mapInfo.spawnSites[team]);
        p.reset(pos.x, pos.y, team);
    }

    for (ProtDrop &d: startingDrops){
        switch (d.type)
        {
        case  SNIPER:
            addDrop(new Sniper(this, config), d.pos.x+CELL_SIZE/2, d.pos.y+CELL_SIZE/2);
            break;
        case  SHOTGUN:
            addDrop(new Shotgun(this, config), d.pos.x+CELL_SIZE/2, d.pos.y+CELL_SIZE/2);
            break;
            case  RIFLE:
            addDrop(new Rifle(this, config), d.pos.x+CELL_SIZE/2, d.pos.y+CELL_SIZE/2);
            break;
        
        default:
            break;
        }
    }
}

b2Vec2 World::getValidPosition(RectArea area){
    b2Vec2 pos;
    EntityChecker checker(b2world);
    int tries = 0;
    do{
        float r = ((float) rand()) / (float) RAND_MAX;
        pos.x = area.x + (r*area.width);
        r = ((float) rand()) / (float) RAND_MAX;
        pos.y = area.y + (r*area.height);
        tries++;
    } while (checker.areaHasEntities(pos-b2Vec2(0.5, 0.5)
    , pos+b2Vec2(0.5, 0.5)) && tries < 50);

    if (tries == 50){
        throw GeneralException("El spawn es muy chico y no entran los jugadores\n");
    }
    return pos;
}

bool World::bombPlanted(){
    return bomb.planted;
}
