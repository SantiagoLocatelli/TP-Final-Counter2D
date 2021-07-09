#ifndef _MAP_INFO_H_
#define _MAP_INFO_H_

#include <vector>
#include <list>
#include <stdint.h>

struct RectArea{
    float x;
    float y;
    float width;
    float height;
};

struct MapInfo{
    uint16_t height;
    uint16_t length;
    std::vector<uint8_t> tiles; //La matriz de casillas "aplastada" en un vector
    std::list<RectArea> bombSites;
    std::list<RectArea> spawnSites;
};

#endif
