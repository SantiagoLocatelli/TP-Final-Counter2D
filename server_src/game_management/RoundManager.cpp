#include "RoundManager.h"

RoundManager::RoundManager(World &world, GameConfig &config):timer(config.getGame("buyTime")), world(world), config(config), roundState(BUY), terrorIdx(0), counterIdx(1), rounds(0){
    wins[0] = 0;
    wins[1] = 0;
}

GameState RoundManager::getGameState(){
    if (wins[terrorIdx] == config.getGame("roundsPerSide")+1){
        return T_WON;
    } else if (wins[counterIdx] == config.getGame("roundsPerSide")+1){
        return CT_WON;
    } else if (rounds == 2*config.getGame("roundsPerSide")){
        return TIE;
    } else {
        return PLAYING;
    }
}

void RoundManager::resetRound(){
    if (rounds == config.getGame("roundsPerSide")){
        terrorIdx = 1;
        counterIdx = 0;
        world.resetWorld(true);
    } else {
        world.resetWorld(false);
    }
}

void RoundManager::updateResult(){
    if (world.bombDefused()){
        result = BOMB_DEFUSED;
    }

    if (world.bombExploded()){
        result = BOMB_EXPLODED;
    }

    if (timer <= 0){
        result = TIME_ENDED;
    }

    int t_alive = 0, ct_alive = 0;
    for (const Player &p: world.getPlayers()){
        if (!p.isDead()){
            if (p.getTeam() == TERROR){
                t_alive++;
            } else {
                ct_alive++;
            }
        }
    }

    if (t_alive == 0 && !world.bombPlanted()){
        result = T_DEAD;
    } else if (ct_alive == 0){
        result = CT_DEAD;
    }
}

GameState RoundManager::roundEnded(){
    if (timer <= 0 && !world.bombPlanted()){
        return CT_WON;
    }

    if (world.bombDefused()){
        return CT_WON;
    }

    if (world.bombExploded()){
        return T_WON;
    }

    int t_alive = 0, ct_alive = 0;
    for (const Player &p: world.getPlayers()){
        if (!p.isDead()){
            if (p.getTeam() == TERROR){
                t_alive++;
            } else {
                ct_alive++;
            }
        }
    }

    if (t_alive == 0 && !world.bombPlanted()){
        return CT_WON;
    } else if (ct_alive == 0){
        return T_WON;
    }

    return PLAYING;
}

bool RoundManager::step(float delta){
    timer -= delta;
    if (timer < 0)
        timer = 0;

    switch (roundState)
    {
    case BUY:
        if (timer <= 0){
            timer = config.getGame("roundTime");
            roundState = MIDDLE;
            return true;
        } else {
            return false;
        }
        break;
    
    case MIDDLE:
        if (roundEnded() != PLAYING){
            updateResult();
            timer = config.getGame("endTime");
            roundState = END;
            int tMoney, ctMoney;
            if (roundEnded() == T_WON){
                wins[terrorIdx]++;
                tMoney = config.getGame("wonRoundMoney");
                ctMoney = config.getGame("lostRoundMoney");
            } else {
                wins[counterIdx]++;
                ctMoney = config.getGame("wonRoundMoney");
                tMoney = config.getGame("lostRoundMoney");
            }
            rounds++;
            for (Player &p: world.getPlayers()){
                if (p.getTeam() == TERROR){
                    p.addMoney(tMoney);
                } else {
                    p.addMoney(ctMoney);
                }
            }

            return false;
        } else {
            return true;
        }
        break;
    
    case END:
        if (timer <= 0 ){
            timer = config.getGame("buyTime");
            if (getGameState() == PLAYING){
                resetRound();
                roundState = BUY;
            }
        }
        return false;
        break;
    }

    return false; //Se supone que acá no llego nunca
}

RoundState RoundManager::getRoundState(){
    return roundState;
}

float RoundManager::getTime(){
    return this->timer;
}

RoundResult RoundManager::getRoundResult(){
    return result;
}

std::array<uint8_t, 2> RoundManager::getRoundScore(){
    return wins;
}

