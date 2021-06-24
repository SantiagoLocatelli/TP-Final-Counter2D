#include "texture_map.h"

void TextureMap::insert(int key, std::unique_ptr<GameObject> value){
    this->map.insert(key, value);
}

std::unique_ptr<GameObject> TextureMap::operator[](int key){
    return this->map[key];
}