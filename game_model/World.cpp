#include "World.h"
#include <utility>

World::World(int grid_length, int grid_height):world(b2Vec2(0,0)){
    grid_size.x = grid_length;
    grid_size.y = grid_height;
}

void World::addBox(int grid_x, int grid_y){
    //TODO: Hacer chequeos de limites en la grilla

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_staticBody;
    boxBodyDef.position.Set(grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f);
    b2Body* box = world.CreateBody(&boxBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(CELL_SIZE/2.0f,CELL_SIZE/2.0f);

    box->CreateFixture(&boxShape, 0);
}

Player& World::createPlayer(int grid_x, int grid_y){
    int id = players.size(); 
    players.emplace(id
    , Player(this->world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f));

    return players.at(id);
}

void World::step(){
    for (std::pair<const int, Player> &p: players){
        p.second.update_velocity();
    }
    world.Step(1.0/30.0, 8, 3);
}

bool World::rayCast(float start_x, float start_y, float angle
, Player *&player, float &distance){
    float min_dist = -1;
    for (std::pair<const int, Player> &p : players){
        float dist = p.second.isHitBy(start_x, start_y, angle);

        if (dist < 0){
            continue;
        }

        if (min_dist == -1){
            min_dist = dist;
            player = &players.at(p.first);
            distance = dist;
        } else if (dist < min_dist){
            min_dist = dist;
            player = &players.at(p.first);
            distance = dist;
        }
    }

    return min_dist != -1;
}
