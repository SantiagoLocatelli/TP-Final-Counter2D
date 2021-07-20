#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include "macros.h"
#include <utility>
#include <stdio.h>

void TextureFactory::unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::unique_ptr<SdlTexture>>& textures,
 std::vector<int>& mapSize, SdlRenderer& renderer){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    YAML::Node size = yaml_map["mapSize"];
    mapSize = size.as<std::vector<int>>();

    //Initialize the objects
    YAML::Node textureNumbers = yaml_map["map"];
    for (YAML::iterator it = textureNumbers.begin(); it != textureNumbers.end(); it++){
        int type = it->as<int>();
        std::string path = map[type].texturePath;
        textures.emplace_back(new SdlTexture(renderer, path, type));
    }
}

void TextureFactory::unmarshalWeapons(const char *yamlFile, std::vector<int>& weaponTypes){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    //Initialize the objects
    YAML::Node weaponsNumbers = yaml_map["weapons"];
    for (YAML::iterator it = weaponsNumbers.begin(); it != weaponsNumbers.end(); it++){
        weaponTypes.push_back(it->as<int>());
    }
}

void TextureFactory::unmarshalSites(const char *yamlFile, std::map<std::string, std::unique_ptr<Draggable>>& rectSites, SdlRenderer& renderer, const int& tile_size){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node Site = yaml_map["spawnSite"];
    std::vector<float> position = Site["T"]["position"].as<std::vector<float>>();
    std::vector<float> size = Site["T"]["size"].as<std::vector<float>>();

    rectSites.emplace("T", new Draggable(renderer, SPAWN_SITE_T, (int) (position[0] * tile_size), (int) (position[1] * tile_size), 0, 255, 0));
    rectSites["T"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));

    position = Site["CT"]["position"].as<std::vector<float>>();
    size = Site["CT"]["size"].as<std::vector<float>>();

    rectSites.emplace("CT", new Draggable(renderer, SPAWN_SITE_CT, (int) (position[0] * tile_size), (int) (position[1] * tile_size), 0, 255, 0));
    rectSites["CT"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));

    position = Site["A"]["position"].as<std::vector<float>>();
    size = Site["A"]["size"].as<std::vector<float>>();

    rectSites.emplace("A", new Draggable(renderer, BOMB_SITE_A, (int) (position[0] * tile_size), (int) (position[1] * tile_size), 255, 0, 0));
    rectSites["A"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));

    position = Site["B"]["position"].as<std::vector<float>>();
    size = Site["B"]["size"].as<std::vector<float>>();

    if (size[0] != 0){
        rectSites.emplace("B", new Draggable(renderer, BOMB_SITE_B, (int) (position[0] * tile_size), (int) (position[1] * tile_size), 255, 0, 0));
        rectSites["B"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));
    }
}
