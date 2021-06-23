#ifndef _WORLD_H_
#define _WORLD_H_

#define CELL_SIZE 1.0f

#include "Player.h"
#include <box2d/box2d.h>
#include <map>

class World{
    private:
        b2World world;
        b2Vec2 grid_size;
        std::map<int, Player> players;

    public:
        World(int grid_length, int grid_height);
        void addBox(int grid_x, int grid_y);
        Player& createPlayer(int grid_x, int grid_y);
        void step();
        bool rayCast(float start_x, float start_y, float angle
        , Player *&player, float &distance);
};

#endif
