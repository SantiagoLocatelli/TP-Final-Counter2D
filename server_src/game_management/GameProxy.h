#ifndef _GAME_PROXY_H_
#define _GAME_PROXY_H_

#include "../game_model/World.h"
#include "../game_model/Player.h"
#include "../../common_src/MapInfo.h"
#include "CompleteModelInfo.h"
#include "RoundManager.h"

class CompleteModelInfo;

#include <vector>
#include <string>

class GameProxy{
    private:
        World* world;
        MapInfo mapInfo;
        GameConfig &config;
        RoundManager *roundManager;
    
    public:
        explicit GameProxy(const std::string &yamlPath, GameConfig &config);

        void setUpGame();
        void step(float delta);
        void clearFrameEvents();
        bool ended();     

        void createPlayer(Team team);
        Player &getPlayer(int id);

        MapInfo getMapInfo();
        CompleteModelInfo getModelInfo();
        RoundState getRoundState();

        ~GameProxy();

        GameProxy(const GameProxy&) = delete;
        GameProxy& operator=(const GameProxy&) = delete;
};

#endif
