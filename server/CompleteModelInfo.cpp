#include "CompleteModelInfo.h"

ModelInfo CompleteModelInfo::getModelInfo(int id){
    ModelInfo info;
    for (int i = 0; i < players.size(); i++){
        if (i == id){
            info.you = players[i];
        } else {
            Prot_Player p;
            p.x = players[i].x;
            p.y = players[i].y;
            p.angle = players[i].angle;
            info.players.push_back(p);
        }
        i++;
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
