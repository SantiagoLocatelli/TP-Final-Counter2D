#ifndef __GAME_H__
#define __GAME_H__

#include "../common/MapInfo.h"
#include "../common/ModelInfo.h"
#include "Character/character.h"
#include "../Sdl/background.h"

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
