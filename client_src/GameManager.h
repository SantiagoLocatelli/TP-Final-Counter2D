#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "GameViewer.h"
#include "levelInfo.h"
#include "SoundEffects.h"


class GameManager {
private:

public:

    GameManager();
    
    void initializeLevel(LevelInfo& level, const MapInfo& map, const ModelInfo& model);
    void updatedLevel(LevelInfo& level, const ModelInfo& model);
};

#endif
