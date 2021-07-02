#include "World.h"
#include <utility>

World::World(int grid_length, int grid_height):b2world(b2Vec2(0,0)){
    gridSize[0] = grid_length;
    gridSize[1] = grid_height;
}

void World::addBox(int grid_x, int grid_y){
    //TODO: Hacer chequeos de limites en la grilla
    boxes.push_back(Box(b2world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f));
    hittables.push_back(&boxes.back());
}

Player& World::createPlayer(float start_x, float start_y){
    players.push_back(Player(*this, start_x, start_y));
    hittables.push_back(&players.back());

    return players.back();
}

void World::step(){
    for (Player &p: players){
        p.updateVelocity();
    }
    b2world.Step(1.0/30.0, 10, 9);
}

bool World::rayCast(Ray ray, Hittable *&hittable, float &distance){
    float min_dist = -1;
    for (Hittable *h : hittables){
        float dist = h->isHitBy(ray);

        if (dist < 0){
            continue;
        }

        if (min_dist == -1 || dist < min_dist){
            min_dist = dist;
            hittable = h;
            distance = dist;
        }
    }

    return min_dist != -1;
}
