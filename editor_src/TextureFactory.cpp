#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <utility>
#include <stdio.h>

/*TextureFactory::TextureFactory(const char *yamlTextureFile, const char *yamlMapFile){
    YAML::Node yamlTexture = YAML::LoadFile(yamlTextureFile);
    YAML::Node yamlMap = YAML::LoadFile(yamlMapFile);
}*/

void TextureFactory::unmarshalTextures(const char *yamlFile, TextureMap& map){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    YAML::Node yaml_keys = yaml_map["textureNumber"];
    YAML::Node yaml_paths = yaml_map["texturePaths"];

    std::vector<int> keys;
    std::vector<std::string> paths;

    for (YAML::iterator it = yaml_keys.begin(); it != yaml_keys.end(); it++) {
        keys.push_back(it->as<int>());
    }

    for (YAML::iterator it = yaml_paths.begin(); it != yaml_paths.end(); it++){
        paths.push_back(it->as<std::string>());
    }

    for (int i = 0; i < keys.size(); i++){
        map.insert(keys[i], paths[i]);
    }
}

void TextureFactory::unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::shared_ptr<SdlTexture>>& textures,
 std::vector<int>& mapSize, SdlRenderer& renderer){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    YAML::Node size = yaml_map["size"];
    mapSize = size.as<std::vector<int>>();

    //Initialize the objects
    YAML::Node textureNumbers = yaml_map["map"];
    for (YAML::iterator it = textureNumbers.begin(); it != textureNumbers.end(); it++){
        int type = it->as<int>();
        std::string path = map[type];
        textures.emplace_back(new SdlTexture(renderer, path, type));
    }
}

void TextureFactory::unmarshalBombSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node Site = yaml_map["bombSite"];

    std::vector<int> position = Site["A"]["position"].as<std::vector<int>>();
    std::vector<int> size = Site["A"]["size"].as<std::vector<int>>();

    bombSites.emplace("A", new Draggable(renderer, "../../common_src/img/bombSite.png", position[0], position[1], 255, 0, 0));
    bombSites["A"]->setWidthAndHeight(size[0], size[1]);

    position = Site["B"]["position"].as<std::vector<int>>();
    size = Site["B"]["size"].as<std::vector<int>>();

    bombSites.emplace("B", new Draggable(renderer, "../../common_src/img/bombSite.png", position[0], position[1], 255, 0, 0));
    bombSites["B"]->setWidthAndHeight(size[0], size[1]);
}

void TextureFactory::unmarshalSpawnSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node Site = yaml_map["spawnSite"];
    std::vector<int> position = Site["T"]["position"].as<std::vector<int>>();
    std::vector<int> size = Site["T"]["size"].as<std::vector<int>>();

    bombSites.emplace("T", new Draggable(renderer, "../../common_src/img/spawnSite.png", position[0], position[1], 0, 255, 0));
    bombSites["T"]->setWidthAndHeight(size[0], size[1]);

    position = Site["CT"]["position"].as<std::vector<int>>();
    size = Site["CT"]["size"].as<std::vector<int>>();

    bombSites.emplace("CT", new Draggable(renderer, "../../common_src/img/spawnSite.png", position[0], position[1], 0, 255, 0));
    bombSites["CT"]->setWidthAndHeight(size[0], size[1]);
}
