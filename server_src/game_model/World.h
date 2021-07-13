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
#include "../../common_src/ModelInfo.h"

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
        float timer;
        ProtBomb bomb;
        std::list<RectArea> bombSites;
        std::vector<RectArea> spawnSites;

        bool positionInArea(float x, float y, RectArea area);

    public:
        b2World b2world;
        GameConfig &config;     

        World(int grid_length, int grid_height, GameConfig &config);
        void addBox(int grid_x, int grid_y);
        void createPlayer(RectArea spawn, Team team);
        void step(float delta);

        void deleteBody(b2Body *body);
        std::vector<Player> &getPlayers();
        void addBullet(Ray ray);
        std::list<Ray> &getBullets();
        void clearBullets();

        void addDrop(Weapon *weapon, float x, float y);
        std::list<Drop*> getDrops();
        float getTime();
        void addSpawn(RectArea site, Team team);
        void addSite(RectArea site);
        void destroyBody(b2Body *body);

        bool canBuy(Player &player);

        //TODO: Pasar estos métodos a su propia clase 
        bool bombExploded();
        void defuseBomb();
        bool bombDefused();

        //TODO: Hacer estas tres como canBuy (le pasas el player)
        bool canPlant(float x, float y);
        bool canDefuse(float x, float y);
        void plantBomb(float x, float y);



        ProtBomb getBomb();

        ~World();

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};

#endif
