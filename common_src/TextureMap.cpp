#include "TextureMap.h"
#include "yaml-cpp/yaml.h"

TextureMap::TextureMap(){
	YAML::Node yaml_map = YAML::LoadFile("TextureMap.yaml");
	int i = 0;
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        TextureInfo info;
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        info.texturePath = texture.first;
        info.isBox = texture.second == 1;
        map[i] = info;
        i++;
    }
}

TextureInfo TextureMap::operator[](int key){
	return this->map.at(key);
}
