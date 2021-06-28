#include "TextureMap.h"
#include <utility>

void TextureMap::insert(int key, std::string value){
    this->map.insert({ key, value });
}

std::string TextureMap::operator[](int key){
    //try catch si la key no existe
    return this->map.at(key);
}

int TextureMap::size(){
    return this->map.size();
}