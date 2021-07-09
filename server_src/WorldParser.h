#ifndef _WORLD_PARSER_H_
#define _WORLD_PARSER_H_

#include "game_model/World.h"
#include "../common_src/MapInfo.h"
#include "yaml-cpp/yaml.h"
#include <stdint.h>
#include <string>
#include <list>
#include <vector>

class WorldParser{
    private:
        YAML::Node mapYaml;

    public:
        explicit WorldParser(const std::string &yamlPath);
        void get_size(uint16_t &length, uint16_t &height);
        std::list<int [2]> get_boxes();
        std::vector<uint8_t> get_tiles();
        std::list<RectArea> get_sites();
        std::list<RectArea> get_spawn();
};

#endif
