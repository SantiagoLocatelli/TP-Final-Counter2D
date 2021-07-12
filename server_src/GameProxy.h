#ifndef _GAME_PROXY_H_
#define _GAME_PROXY_H_

#include "game_model/World.h"
#include "game_model/Player.h"
#include "../common_src/MapInfo.h"
#include "CompleteModelInfo.h"

class CompleteModelInfo;

#include <vector>
#include <string>

class GameProxy{
    private:
        World* world;
        MapInfo mapInfo;
        GameConfig &config;
    
    public:
        explicit GameProxy(const std::string &yamlPath, GameConfig &config);
        void step();        

        MapInfo getMapInfo();
        CompleteModelInfo getModelInfo();

        //Crea un jugador 
        void createPlayer(Team team);

        //TODO: Es muy engorroso tener una funcion diferente para cada accion.
        void toggleMovement(int id, Direction direction);
        void setAngle(int id, float angle);
        void toggleWeapon(int id);
        void reloadWeapon(int id);
        void changeWeapon(int id, WeaponSlot slot);
        void dropWeapon(int id);
        void toggleDefuse(int id);

        void clearFrameEvents();

        bool ended();

        ~GameProxy();

        GameProxy(const GameProxy&) = delete;
        GameProxy& operator=(const GameProxy&) = delete;
};

#endif
