#include "World.h"
#include <utility>

World::World(int grid_length, int grid_height):player_number(0), b2world(b2Vec2(0,0)){
    gridSize[0] = grid_length;
    gridSize[1] = grid_height;
    b2world.SetContactListener(&collisionHandler);
}

void World::addBox(int grid_x, int grid_y){
    //TODO: Hacer chequeos de limites en la grilla
    boxes.push_back(Box(b2world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f));
}

void World::createPlayer(float start_x, float start_y){
    players.emplace_back(std::move(Player(*this, start_x, start_y)));
}

std::vector<Player> &World::getPlayers(){
    return players;
}

void World::step(){
    for (Player &p: players){
        if (!p.isDead())
            p.updateVelocity();
    }
    b2world.Step(1.0/30.0, 10, 9);
    for (b2Body *b : bodiesToDestroy){
        //Aca elimino todos los drops
        delete (Drop *)b->GetFixtureList()->GetUserData().pointer;
        b2world.DestroyBody(b);
    }
    bodiesToDestroy.clear();
    bullets.clear();
}

bool World::rayCast(Ray &ray, Hittable *&hittable){
    float min_dist = -1;
    for (Player &p: players){
        if (!p.isDead()){
            float dist = p.isHitBy(ray);

            if (dist < 0){
                continue;
            }

            if (min_dist == -1 || dist < min_dist){
                min_dist = dist;
                hittable = &p;
                ray.distance = dist;
            }
        }
    }

    //TODO: Repito codigo, mejorar esta parte
    for (Box &b: boxes){
        float dist = b.isHitBy(ray);

        if (dist < 0){
            continue;
        }

        if (dist < min_dist){
            min_dist = dist;
            hittable = &b;
            ray.distance = dist;
        }
    }

    return min_dist != -1;
}

void World::deleteBody(b2Body *body){
    b2world.DestroyBody(body);
}

void World::addBullet(Ray ray){
    bullets.push_back(ray);
}

std::list<Ray> &World::getBullets(){
    return bullets;
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

