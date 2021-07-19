#include "TextureMap.h"
#include "yaml-cpp/yaml.h"

TextureMap::TextureMap(){
	YAML::Node yaml_map = YAML::LoadFile("/usr/local/share/counter2d/resources/common/utils/TextureMap.yaml");
	int i = 0;
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        TextureInfo info;
        std::pair<std::string, std::vector<int>> texture = it->as<std::pair<std::string, std::vector<int>>>();
        info.texturePath = texture.first;
        info.isBox = texture.second[4] == 1;
        info.clip = {texture.second[0], texture.second[1], texture.second[2], texture.second[3]};
        map[i] = info;
        i++;
    }
}

TextureInfo TextureMap::operator[](int key){
	return this->map.at(key);
}

int TextureMap::size(){
    return this->map.size();
}
