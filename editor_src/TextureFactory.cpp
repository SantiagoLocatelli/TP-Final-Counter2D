#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <utility>
#include <stdio.h>

void TextureFactory::unmarshalTextures(char *yamlFile, TextureMap& map){
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

void TextureFactory::unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::unique_ptr<SdlTexture>>& textures, SdlRenderer& renderer){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    //Initialize the objects
    YAML::Node textureNumbers = yaml_map["map"];
    for (YAML::iterator it = textureNumbers.begin(); it != textureNumbers.end(); it++){
        int type = it->as<int>();
        std::string path = map[type];
        textures.emplace_back(new SdlTexture(renderer, path, type));
    }
}

void TextureFactory::unmarshalBombSites(const char *yamlFile, SDL_Rect& bombSiteA, SDL_Rect& bombSiteB){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node bombSite = yaml_map["bombSite"];
    std::vector<int> position = bombSite["A"]["position"].as<std::vector<int>>();
    std::vector<int> size = bombSite["A"]["size"].as<std::vector<int>>();

    bombSiteA.x = position[0];
    bombSiteA.y = position[1];
    bombSiteA.w = size[0];
    bombSiteA.h = size[1];

    position = bombSite["B"]["position"].as<std::vector<int>>();
    size = bombSite["B"]["size"].as<std::vector<int>>();

    bombSiteB.x = position[0];
    bombSiteB.y = position[1];
    bombSiteB.w = size[0];
    bombSiteB.h = size[1];
}

void TextureFactory::unmarshalSpawnSites(const char *yamlFile, SDL_Rect& spawnSiteT, SDL_Rect& spawnSiteCT){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);
    YAML::Node spawnSite = yaml_map["spawnSite"];
    std::vector<int> position = spawnSite["T"]["position"].as<std::vector<int>>();
    std::vector<int> size = spawnSite["T"]["size"].as<std::vector<int>>();

    spawnSiteT.x = position[0];
    spawnSiteT.y = position[1];
    spawnSiteT.w = size[0];
    spawnSiteT.h = size[1];

    position = spawnSite["CT"]["position"].as<std::vector<int>>();
    size = spawnSite["CT"]["size"].as<std::vector<int>>();

    spawnSiteCT.x = position[0];
    spawnSiteCT.y = position[1];
    spawnSiteCT.w = size[0];
    spawnSiteCT.h = size[1];
}
