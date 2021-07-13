#include "World.h"
#include <utility>
#include "EntityChecker.h"
#include "../../common_src/GeneralException.h"

World::World(int grid_length, int grid_height, GameConfig &config):player_number(0), timer(0), b2world(b2Vec2(0,0)), config(config){
    gridSize[0] = grid_length;
    gridSize[1] = grid_height;
    bomb.planted = false;
    b2world.SetContactListener(&collisionHandler);
    spawnSites.reserve(2);
}

void World::addBox(int grid_x, int grid_y){
    if(grid_x < 0 || grid_x > gridSize[0] || grid_y < 0 || grid_y > gridSize[1])
        throw GeneralException("Posicicon para `addBox` fuera de límites");
    boxes.push_back(Box(b2world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f));
}

void World::createPlayer(RectArea spawn, Team team){
    float start_x, start_y;
    EntityChecker checker(b2world);

    int tries = 0;
    do{
        float r = ((float) rand()) / (float) RAND_MAX;
        start_x = spawn.x + (r*spawn.width);
        r = ((float) rand()) / (float) RAND_MAX;
        start_y = spawn.y + (r*spawn.height);
        tries++;
    } while (checker.areaHasEntities(b2Vec2(start_x-0.5, start_y-0.5)
    , b2Vec2(start_x+0.5, start_y+0.5)) && tries < 50);

    if (tries == 50){
        throw GeneralException("El spawn es muy chico y no entran los jugadores\n");
    }

    players.emplace_back(std::move(Player(*this, start_x, start_y, config, team)));
}

std::vector<Player> &World::getPlayers(){
    return players;
}

void World::step(float delta){
    timer += delta;
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


float World::getTime(){
    return timer;
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

void World::addSite(RectArea site){
    bombSites.push_back(site);
}

void World::addSpawn(RectArea site, Team team){
    spawnSites[team] = site;
}


bool World::canPlant(float x, float y){
    if (bomb.planted)
        return false;

    for (const RectArea &site: bombSites){
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
    return positionInArea(player.getPosition()[0], player.getPosition()[1], spawnSites[player.getTeam()]);
}

bool World::positionInArea(float x, float y, RectArea area){
    return (x > area.x && x < area.x+area.width && y > area.y && y < area.y+area.height);
}