#ifndef _GAME_PROXY_H_
#define _GAME_PROXY_H_

#include "../game_model/World.h"
#include "../game_model/Player.h"
#include "../common/MapInfo.h"
#include "CompleteModelInfo.h"

#include <vector>
#include <string>

class GameProxy{
    private:
        World* world;
        std::vector<Player> players;
        MapInfo mapInfo;
    
    public:
        explicit GameProxy(const std::string &yamlPath);
        void step();        

        MapInfo getMapInfo();
        CompleteModelInfo getModelInfo();

        //Crea un jugador y devuelve el id que lo representa
        int createPlayer(int team);

        void toggleMovement(int id, Direction direction);
        void rotate(int id, float angle);
        void activateWeapon(int id);

        bool ended();

        ~GameProxy();
};

#endif
