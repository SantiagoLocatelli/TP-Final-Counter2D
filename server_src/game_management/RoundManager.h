#ifndef _ROUND_MANAGER_H_
#define _ROUND_MANAGER_H_

#include "../game_model/World.h"
#include "../game_model/GameConfig.h"

enum RoundState{BUY, MIDDLE, END};
enum GameState{PLAYING, T_WON, CT_WON, TIE};

class RoundManager{
    private:
        float timer;
        World &world;
        GameConfig &config;
        RoundState roundState;
        int wins[2];
        int terrorIdx;
        int counterIdx;
        int rounds;

        GameState roundEnded();
    public:
        RoundManager(World &world, GameConfig &config);
        void resetRound();
        bool step(float delta);
        RoundState getRoundState();
        GameState gameEnded();
};

#endif
