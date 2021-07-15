#ifndef _COMLETE_MODEL_INFO_H_
#define _COMLETE_MODEL_INFO_H_

#include "../../common_src/ModelInfo.h"
#include "GameProxy.h"
#include <list>
#include <vector>

class CompleteModelInfo{
    private:
        std::vector<You> players;
        std::list<Bullet> bullets;
        std::list<ProtDrop> drops;
        bool game_ended;
        ProtBomb bomb;
        float timeRemaining;
        RoundState roundState;
    
    public:
        CompleteModelInfo() = default;
        CompleteModelInfo(CompleteModelInfo&& other);
        ModelInfo getModelInfo(int id);
        bool ended();
        CompleteModelInfo& operator=(CompleteModelInfo&& other);
    
    friend class GameProxy;
};

#endif
