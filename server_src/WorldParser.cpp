#include "WorldParser.h"
#include "../common_src/TextureMap.h"
#include <vector>

WorldParser::WorldParser(const std::string &yamlPath)
:mapYaml(YAML::LoadFile(yamlPath)){}

void WorldParser::get_size(uint16_t &length, uint16_t &height){
    std::vector<int> size = mapYaml["mapSize"].as<std::vector<int>>();
    length = size[0];
    height = size[1];
}

std::list<ProtBox> WorldParser::get_boxes(){
    TextureMap textureMap;
    std::list<ProtBox> boxList;
    std::vector<int> map = mapYaml["map"].as<std::vector<int>>();
    uint16_t height, length;
    get_size(length, height);
    
    for (size_t i = 0; i < map.size(); i++){
        if (textureMap[map[i]].isBox){
            ProtBox b;
            b.x = i%length;
            b.y = i/height;
            boxList.push_back(b);
        }
    }

    return boxList;
}