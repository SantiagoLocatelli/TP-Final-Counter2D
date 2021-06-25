#ifndef _MAP_INFO_H_
#define _MAP_INFO_H_

#include <list>

struct Box{
    uint16_t x;
    uint16_t y;
};

struct MapInfo{
    uint16_t height;
    uint16_t length;
    std::list<Box> boxes;
};

#endif
