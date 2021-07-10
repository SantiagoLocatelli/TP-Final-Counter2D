#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "GameViewer.h"
#include "levelInfo.h"
#include "SoundEffects.h"


class GameManager {
private:
    LevelInfo level;

public:

    GameManager();
    
    LevelInfo initializeLevel(const MapInfo& map, const ModelInfo& model);
    LevelInfo updatedLevel(const ModelInfo& model);
};

#endif
