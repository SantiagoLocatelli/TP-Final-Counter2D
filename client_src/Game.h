#ifndef __GAME_H__
#define __GAME_H__

#include "../common_src/MapInfo.h"
#include "../common_src/ModelInfo.h"
#include "Character/character.h"
#include "../common_src/Sdl/background.h"

class Game {
private:

    MapInfo map;
    ModelInfo model;
    Character pj;
    Background bg;

public:

    Game(MapInfo map, ModelInfo model, Character pj, Background bg);

};

#endif
