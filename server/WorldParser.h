#ifndef _WORLD_PARSER_H_
#define _WORLD_PARSER_H_

#include "../protocol/MapInfo.h"
#include "../game_model/World.h"
#include <string>
#include <list>

class WorldParser{
    public:
        explicit WorldParser(const std::string &yamlPath);
        void get_size(int &length, int &height);
        std::list<Box> get_boxes();
        void fill_world(World *world);
};

#endif
