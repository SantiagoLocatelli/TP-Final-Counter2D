#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "GameViewer.h"
#include "levelInfo.h"


class GameManager {
private:

public:

    GameManager();
    
    static void initializeLevel(const MapInfo& map, const ModelInfo& model, LevelInfo& level);
    static void updatedLevel(const ModelInfo& model, LevelInfo& level);
};

#endif
