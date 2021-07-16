#include "RoundManager.h"

RoundManager::RoundManager(World &world, GameConfig &config):timer(0), world(world), config(config), roundState(BUY), terrorIdx(0), counterIdx(1), rounds(0){
    wins[0] = 0;
    wins[1] = 0;
}

GameState RoundManager::gameEnded(){
    if (wins[terrorIdx] == config.getGame().at("roundsPerSide")+1){
        return T_WON;
    } else if (wins[counterIdx] == config.getGame().at("roundsPerSide")+1){
        return CT_WON;
    } else if (rounds == 2*config.getGame().at("roundsPerSide")){
        return TIE;
    } else {
        return PLAYING;
    }
}

void RoundManager::resetRound(){
    if (rounds == config.getGame().at("roundsPerSide")){
        terrorIdx = 1;
        counterIdx = 0;
        world.resetWorld(true);
    } else {
        world.resetWorld(false);
    }
}

GameState RoundManager::roundEnded(){
    if (timer > config.getGame().at("roundTime") || world.bombDefused())
        return CT_WON;

    if (world.bombExploded())
        return T_WON;

    //TODO: Chequear por equipo en vez de por personas individuales
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
    timer += delta;

    switch (roundState)
    {
    case BUY:
        if (timer > config.getGame().at("buyTime")){
            timer = 0;
            roundState = MIDDLE;
            return true;
        } else {
            return false;
        }
        break;
    
    case MIDDLE:
        if (roundEnded() != PLAYING){
            timer = 0;
            roundState = END;
            if (roundEnded() == T_WON){
                wins[terrorIdx]++;
            } else {
                wins[counterIdx]++;
            }
            rounds++;
            return false;
        } else {
            return true;
        }
        break;
    
    case END:
        if (timer > config.getGame().at("endTime")){
            timer = 0;
            resetRound();
            roundState = BUY;
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
