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
#include "../../common_src/MapInfo.h"

class Drop;
class Player;

class World{
    private:
        std::vector<Player> players;
        std::list<Box> boxes;
        std::list<Ray> bullets;
        int player_number;
        CollisionHandler collisionHandler;
        std::list<b2Body*> bodiesToDestroy;
        ProtBomb bomb;
        MapInfo mapInfo;
        std::list<ProtDrop> startingDrops;

        bool positionInArea(float x, float y, RectArea area);
        b2Vec2 getValidPosition(RectArea area);

    public:
        b2World b2world;
        GameConfig &config;     

        World(MapInfo mapInfo, GameConfig &config);
        void addBox(int grid_x, int grid_y);
        void createPlayer(Team team);
        void step(float delta);

        void deleteBody(b2Body *body);
        std::vector<Player> &getPlayers();
        void addBullet(Ray ray);
        std::list<Ray> &getBullets();
        void clearBullets();

        void addDrop(Weapon *weapon, float x, float y);
        void addStartingDrop(ProtDrop drop);
        std::list<Drop*> getDrops();
        void destroyBody(b2Body *body);

        bool bombExploded();
        void defuseBomb();
        bool bombDefused();
        bool bombPlanted();

        bool canPlant(float x, float y);
        bool canDefuse(float x, float y);
        void plantBomb(float x, float y);

        void resetWorld(bool changeTeams);

        ProtBomb getBomb();

        ~World();

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};

#endif
