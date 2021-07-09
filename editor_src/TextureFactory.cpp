#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <utility>
#include <stdio.h>

/*TextureFactory::TextureFactory(const char *yamlTextureFile, const char *yamlMapFile){
    YAML::Node yamlTexture = YAML::LoadFile(yamlTextureFile);
    YAML::Node yamlMap = YAML::LoadFile(yamlMapFile);
}*/

void TextureFactory::unmarshalMap(const char *yamlFile, TextureMap& map, std::list<std::unique_ptr<SdlTexture>>& textures,
 std::vector<float>& mapSize, SdlRenderer& renderer){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    YAML::Node size = yaml_map["mapSize"];
    mapSize = size.as<std::vector<float>>();

    //Initialize the objects
    YAML::Node textureNumbers = yaml_map["map"];
    for (YAML::iterator it = textureNumbers.begin(); it != textureNumbers.end(); it++){
        int type = it->as<int>();
        std::string path = map[type].texturePath;
        textures.emplace_back(new SdlTexture(renderer, path, type));
    }
}

void TextureFactory::unmarshalBombSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer, const int& tile_size){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node Site = yaml_map["bombSite"];

    std::vector<float> position = Site["A"]["position"].as<std::vector<float>>();
    std::vector<float> size = Site["A"]["size"].as<std::vector<float>>();

    bombSites.emplace("A", new Draggable(renderer, "../../common_src/img/bombSite.png", (int) (position[0] * tile_size), (int) (position[1] * tile_size), 255, 0, 0));
    bombSites["A"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));

    position = Site["B"]["position"].as<std::vector<float>>();
    size = Site["B"]["size"].as<std::vector<float>>();

    bombSites.emplace("B", new Draggable(renderer, "../../common_src/img/bombSite.png", (int) (position[0] * tile_size), (int) (position[1] * tile_size), 255, 0, 0));
    bombSites["B"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));
}

void TextureFactory::unmarshalSpawnSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer, const int& tile_size){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node Site = yaml_map["spawnSite"];
    std::vector<float> position = Site["T"]["position"].as<std::vector<float>>();
    std::vector<float> size = Site["T"]["size"].as<std::vector<float>>();

    bombSites.emplace("T", new Draggable(renderer, "../../common_src/img/spawnSite.png", (int) (position[0] * tile_size), (int) (position[1] * tile_size), 0, 255, 0));
    bombSites["T"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));

    position = Site["CT"]["position"].as<std::vector<float>>();
    size = Site["CT"]["size"].as<std::vector<float>>();

    bombSites.emplace("CT", new Draggable(renderer, "../../common_src/img/spawnSite.png", (int) (position[0] * tile_size), (int) (position[1] * tile_size), 0, 255, 0));
    bombSites["CT"]->setWidthAndHeight((int) (size[0] * tile_size), (int) (size[1] * tile_size));
}
