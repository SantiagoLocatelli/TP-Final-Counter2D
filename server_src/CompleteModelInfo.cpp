#include "CompleteModelInfo.h"

ModelInfo CompleteModelInfo::getModelInfo(int id){
    ModelInfo info;
    for (int i = 0; i < (int)players.size(); i++){
        if (i == id){
            info.you = players[i];
        } else {
            ProtPlayer p;
            p.x = players[i].x;
            p.y = players[i].y;
            p.angle = players[i].angle;
            p.dead = players[i].dead;
            info.players.push_back(p);
        }
    }

    for (Bullet b: bullets){
        info.bullets.push_back(b);
    }

    info.game_ended = game_ended;

    return info;
}

bool CompleteModelInfo::ended(){
    return game_ended;
}

CompleteModelInfo::CompleteModelInfo(CompleteModelInfo&& other){
    players = std::move(other.players);
    bullets = std::move(other.bullets);
    game_ended = other.game_ended;
}

CompleteModelInfo& CompleteModelInfo::operator=(CompleteModelInfo&& other){
    if (this == &other){
        return *this;
    }

    players = std::move(other.players);
    bullets = std::move(other.bullets);
    game_ended = other.game_ended;
    

    return *this;
}
