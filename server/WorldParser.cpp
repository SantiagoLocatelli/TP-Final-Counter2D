#include "WorldParser.h"
#include <vector>

WorldParser::WorldParser(const std::string &yamlPath)
:mapYaml(YAML::LoadFile(yamlPath)){}

void WorldParser::get_size(int &length, int &height){
    std::vector<int> size = mapYaml["size"].as<std::vector<int>>();
    length = size[0];
    height = size[1];
}

std::list<Box> WorldParser::get_boxes(){
    std::list<Box> boxList;
    YAML::Node boxes = mapYaml["boxes"];
    for (YAML::iterator it = boxes.begin(); it != boxes.end(); ++it) {
        Box b;
        std::vector<int> pos = it->as<std::vector<int>>();
        b.x = pos[0];
        b.y = pos[1];
        boxList.push_back(b);
    }

    return boxList;
}

void WorldParser::fill_world(World *world){
    
}