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

std::list<std::array<int,2>> WorldParser::get_boxes(){
    TextureMap textureMap;
    std::list<std::array<int,2>> boxList;
    std::vector<int> map = mapYaml["map"].as<std::vector<int>>();
    uint16_t height, length;
    get_size(length, height);
    
    for (size_t i = 0; i < map.size(); i++){
        if (textureMap[map[i]].isBox){
            std::array<int, 2> b;
            b[0] = i%length;
            b[1] = i/height;
            boxList.push_back(b);
        }
    }

    return boxList;
}

std::vector<uint8_t> WorldParser::get_tiles(){
    return mapYaml["map"].as<std::vector<uint8_t>>();
}

std::list<RectArea> WorldParser::get_sites(){
    std::list<RectArea> list;
    std::vector<float> position = mapYaml["bombSite"]["A"]["position"].as<std::vector<float>>();
    std::vector<float> size = mapYaml["bombSite"]["A"]["size"].as<std::vector<float>>();

    RectArea r;
    r.x = position[0];
    r.y = position[1];
    r.width = size[0];
    r.height = size[1];
    list.push_back(r);
    try{
        position = mapYaml["bombSite"]["B"]["position"].as<std::vector<float>>();
        size = mapYaml["bombSite"]["B"]["size"].as<std::vector<float>>();

        r.x = position[0];
        r.y = position[1];
        r.width = size[0];
        r.height = size[1];
        list.push_back(r);
    } catch (const YAML::TypedBadConversion<std::vector<float>> &e){
        //Esto significa que no hay B site
    }

    return list;
}

std::list<RectArea> WorldParser::get_spawn(){
    std::list<RectArea> list;
    std::vector<float> position = mapYaml["spawnSite"]["T"]["position"].as<std::vector<float>>();
    std::vector<float> size = mapYaml["bombSite"]["T"]["size"].as<std::vector<float>>();

    RectArea r;
    r.x = position[0];
    r.y = position[1];
    r.width = size[0];
    r.height = size[1];
    list.push_back(r);

    position = mapYaml["spawnSite"]["CT"]["position"].as<std::vector<float>>();
    size = mapYaml["spawnSite"]["CT"]["size"].as<std::vector<float>>();

    r.x = position[0];
    r.y = position[1];
    r.width = size[0];
    r.height = size[1];
    list.push_back(r);

    return list;
}
