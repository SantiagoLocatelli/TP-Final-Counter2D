#include "World.h"

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

Player World::createPlayer(int grid_x, int grid_y){
    return Player(world, grid_x+CELL_SIZE/2.0f, grid_y+CELL_SIZE/2.0f);
}

void World::step(float delta){
    world.Step(delta, 8, 3);
}
