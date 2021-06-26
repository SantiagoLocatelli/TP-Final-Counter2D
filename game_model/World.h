#ifndef _WORLD_H_
#define _WORLD_H_

#define CELL_SIZE 1.0f

#include "Player.h"
#include <box2d/box2d.h>
#include <list>

class World{
    private:
        b2World world;
        b2Vec2 gridSize;
        std::list<Player> players;

    public:
        World(int grid_length, int grid_height);
        void addBox(int grid_x, int grid_y);
        Player& createPlayer(float start_x, float start_y);
        Player& createPlayer(char team);
        void step();
        bool rayCast(float start_x, float start_y, float angle
        , Player *&player, float &distance);
};

#endif
