#include "GameObjectFactory.h"
#include "yaml-cpp/yaml.h"

void GameObjectFactory::unmarshal(char *yaml_file, TextureMap& map){
    YAML::Node yaml_map = YAML::LoadFile(yaml_file);
}