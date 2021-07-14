#ifndef _ROUND_MANAGER_H_
#define _ROUND_MANAGER_H_

#include "../game_model/World.h"
#include "../game_model/GameConfig.h"

enum GameState{BUY, PLAYING, END};

class RoundManager{
    private:
        float timer;
        World &world;
        GameConfig &config;
        GameState state;

        void resetRound();
        bool gameEnded();
    public:
        RoundManager(World &world, GameConfig &config);
        bool step(float delta);
        GameState getState();
};

#endif
