#include "RoundManager.h"

RoundManager::RoundManager(World &world, GameConfig &config):timer(0), world(world), config(config), state(BUY){}

void RoundManager::resetRound(){
}

bool RoundManager::gameEnded(){
    if (timer > config.getGame().at("roundTime") || world.bombExploded() || world.bombDefused()){
        return true;
    }

    //TODO: Chequear por equipo en vez de por personas individuales
    int alive_players = 0;
    for (const Player &p: world.getPlayers()){
        if (!p.isDead()){
            alive_players++;
        }
    }

    return alive_players <= 1;
}

bool RoundManager::step(float delta){
    timer += delta;

    switch (state)
    {
    case BUY:
        if(timer > config.getGame().at("buyTime")){
            timer = 0;
            state = PLAYING;
            return true;
        } else {
            return false;
        }
        break;
    
    case PLAYING:
        if(gameEnded()){
            timer = 0;
            state = END;
            return false;
        } else {
            return true;
        }
        break;
    
    case END:
        if(timer > config.getGame().at("endTime")){
            timer = 0;
            resetRound();
            state = BUY;
            return true;
        } else {
            return false;
        }
        break;
    }

    return false; //Se supone que acá no llego nunca
}

GameState RoundManager::getState(){
    return state;
}
