#ifndef _WORLD_H_
#define _WORLD_H_

#define CELL_SIZE 1.0f

#include "Player.h"
#include <box2d/box2d.h>
#include <list>
#include <vector>
#include "Hittable.h"
#include "Box.h"
#include "Ray.h"
#include "Drop.h"
#include "CollisionHandler.h"
#include "GameConfig.h"
#include "../../common_src/Utils.h"

class Drop;
class Player;

class World{
    private:
        std::array<int, 2> gridSize;
        std::vector<Player> players;
        std::list<Box> boxes;
        std::list<Ray> bullets;
        int player_number;
        CollisionHandler collisionHandler;
        std::list<b2Body*> bodiesToDestroy; 

    public:
        GameConfig config;       
        b2World b2world;

        World(int grid_length, int grid_height);
        void addBox(int grid_x, int grid_y);
        void createPlayer(RectArea spawn, Team team);
        void step();
        float rayCast(Ray ray, Hittable *&hittable);
        std::list<Hittable *> &hittablesInArea(float x, float y, float heigth, float length);

        void deleteBody(b2Body *body);
        std::vector<Player> &getPlayers();
        void addBullet(Ray ray);
        std::list<Ray> &getBullets();
        void clearBullets();

        void addDrop(Weapon *weapon, float x, float y);
        std::list<Drop*> getDrops();

        void destroyBody(b2Body *body);

        ~World();

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};

#endif
