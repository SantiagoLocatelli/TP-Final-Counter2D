#ifndef _MAP_INFO_H_
#define _MAP_INFO_H_

#include <vector>
#include <list>
#include <stdint.h>
#include "Utils.h"

struct MapInfo{
    SkinType ct;
    SkinType tt;
    uint16_t height;
    uint16_t length;
    std::vector<uint8_t> tiles; //La matriz de casillas "aplastada" en un vector
    std::vector<RectArea> bombSites;
    std::vector<RectArea> spawnSites; //El primer spawn es el de terror y el segundo el de counter
};

#endif
