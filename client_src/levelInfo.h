#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include "../../common_src/MapInfo.h"

struct LevelInfo{
    int height;
    int width;
	int h_meters;
	int w_meters;
    std::list<ProtBox> boxes;
};

#endif