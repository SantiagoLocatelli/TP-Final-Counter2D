#include "CompleteModelInfo.h"
#include <utility>

ModelInfo CompleteModelInfo::getModelInfo(int id){
    ModelInfo info = incompleteModel;
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

    return info;
}

bool CompleteModelInfo::ended(){
    return incompleteModel.gameEnded;
}

CompleteModelInfo::CompleteModelInfo(CompleteModelInfo&& other){
    players = std::move(other.players);
    incompleteModel = std::move(other.incompleteModel);
}

CompleteModelInfo& CompleteModelInfo::operator=(CompleteModelInfo&& other){
    if (this == &other){
        return *this;
    }

    players = std::move(other.players);
    incompleteModel = std::move(other.incompleteModel);

    return *this;
}
