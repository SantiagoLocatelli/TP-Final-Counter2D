#include "CompleteModelInfo.h"
#include <utility>

ModelInfo CompleteModelInfo::getModelInfo(int id){
    ModelInfo info;
    for (int i = 0; i < (int)players.size(); i++){
        if (i == id){
            info.you = players[i];
        } else {
            ProtPlayer p;
            p.dead = players[i].dead;
            if (!p.dead){
                p.pos.x = players[i].pos.x;
                p.pos.y = players[i].pos.y;
                p.angle = players[i].angle;
                p.weapons = players[i].weapons;
                p.currentSlot = players[i].currentSlot;
                p.team = players[i].team;
                p.shot = players[i].shot;
            }
            info.players.push_back(p);
        }
    }

    for (Bullet b: bullets){
        info.bullets.push_back(b);
    }

    for (ProtDrop d: drops){
        info.drops.push_back(d);
    }

    info.game_ended = game_ended;
    info.bomb = bomb;
    info.timeRemaining = timeRemaining;
    info.roundState = roundState;

    return info;
}

bool CompleteModelInfo::ended(){
    return game_ended;
}

CompleteModelInfo::CompleteModelInfo(CompleteModelInfo&& other){
    players = std::move(other.players);
    bullets = std::move(other.bullets);
    drops = std::move(other.drops);
    game_ended = other.game_ended;
    bomb = other.bomb;
    timeRemaining = other.timeRemaining;
    roundState = other.roundState;
}

CompleteModelInfo& CompleteModelInfo::operator=(CompleteModelInfo&& other){
    if (this == &other){
        return *this;
    }

    players = std::move(other.players);
    bullets = std::move(other.bullets);
    drops = std::move(other.drops);
    game_ended = other.game_ended;
    bomb = other.bomb;
    timeRemaining = other.timeRemaining;
    roundState = other.roundState;

    return *this;
}
