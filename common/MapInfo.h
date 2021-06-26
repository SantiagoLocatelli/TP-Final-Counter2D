#ifndef _MAP_INFO_H_
#define _MAP_INFO_H_

#include <list>

struct Box{
    int x;
    int y;
};

struct MapInfo{
    int height;
    int length;
    std::list<Box> boxes;
};

#endif
