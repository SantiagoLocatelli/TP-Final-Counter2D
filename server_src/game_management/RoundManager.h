#ifndef _ROUND_MANAGER_H_
#define _ROUND_MANAGER_H_

#include "../game_model/World.h"
#include "../game_model/GameConfig.h"
#include "../../common_src/Utils.h"

class RoundManager{
    private:
        float timer;
        World &world;
        GameConfig &config;
        RoundState roundState;
        RoundResult result;
        std::array<uint8_t, 2> wins;
        int terrorIdx;
        int counterIdx;
        int rounds;

        GameState roundEnded();
        void updateResult();
    public:
        RoundManager(World &world, GameConfig &config);
        void resetRound();
        bool step(float delta);
        RoundState getRoundState();
        GameState getGameState();
        RoundResult getRoundResult();
        std::array<uint8_t, 2> getRoundScore();

        float getTime();
};

#endif
