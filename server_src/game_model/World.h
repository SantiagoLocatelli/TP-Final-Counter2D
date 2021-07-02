#ifndef _WORLD_H_
#define _WORLD_H_

#define CELL_SIZE 1.0f

#include "Player.h"
#include <box2d/box2d.h>
#include <list>
#include "Hittable.h"
#include "Box.h"
#include "Ray.h"

class Player;

class World{
    private:
        std::array<int, 2> gridSize;
        std::list<Player> players;
        std::list<Box> boxes;
        std::list<Hittable*> hittables; 

    public:
        b2World b2world;

        World(int grid_length, int grid_height);
        void addBox(int grid_x, int grid_y);
        Player& createPlayer(float start_x, float start_y);
        void step();
        bool rayCast(Ray ray, Hittable *&hittable, float &distance);

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};

#endif
