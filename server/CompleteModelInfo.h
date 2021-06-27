#ifndef _COMLETE_MODEL_INFO_H_
#define _COMLETE_MODEL_INFO_H_

#include "../common/ModelInfo.h"
#include "GameProxy.h"
#include <list>
#include <vector>

class CompleteModelInfo{
    private:
        std::vector<You> players;
        std::list<Bullet> bullets;
        bool game_ended;
    
    public:
        ModelInfo getModelInfo(int id);
        bool ended();
    
    friend class GameProxy;
};

#endif
