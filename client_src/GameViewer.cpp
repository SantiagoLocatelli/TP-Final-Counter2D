#include "Game.h"

Game::Game(MapInfo map, ModelInfo model, Character pj, Background bg)
    :map(map), model(model), pj(std::move(pj)), bg(std::move(bg)) {}