#include "TextureManager.h"
#include "yaml-cpp/yaml.h"
#include "levelInfo.h"
#include <iostream>

#define PATH "../../client_src/yaml/"



const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};

TextureManager::TextureManager(SdlRenderer& renderer, std::vector<TileInfo> tiles){
    loadTexturesWeapons(renderer);
    loadTiles(renderer, tiles);
    loadSkins(renderer);
}

void TextureManager::loadWeaponsOnFloor(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "weaponsOnFloor.yaml";

    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        WeaponType weapon = (WeaponType) texture.second;
        this->weaponsOnFloor[weapon] = new SdlTexture(renderer, texture.first, NEGRO.r, NEGRO.g, NEGRO.b);
    }
}

void TextureManager::loadWeaponsOnHud(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "weaponsOnHud.yaml";

    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        WeaponType weapon = (WeaponType) texture.second;
        this->weaponsOnHud[weapon] = new SdlTexture(renderer, texture.first, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    }
}

void TextureManager::loadWeaponsOnPlayer(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "weaponsOnPlayer.yaml";

    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        WeaponType weapon = (WeaponType) texture.second;
        this->weaponsOnPj[weapon] = new SdlTexture(renderer, texture.first, NEGRO.r, NEGRO.g, NEGRO.b);
    }
}

void TextureManager::loadWeaponsAnim(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "weaponsAnim.yaml";

    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        WeaponType weapon = (WeaponType) texture.second;
        this->animWeaponOnPj[weapon] = new SdlTexture(renderer, texture.first);
    }
}

void TextureManager::loadTexturesWeapons(SdlRenderer& renderer){
    // enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB, DEFUSER};
    loadWeaponsAnim(renderer);
    loadWeaponsOnFloor(renderer);
    loadWeaponsOnPlayer(renderer);
    loadWeaponsOnHud(renderer);
}


void TextureManager::loadSkins(SdlRenderer& renderer){
    std::stringstream path;
    path << PATH;
    path << "playerSkins.yaml";
    YAML::Node yaml_map = YAML::LoadFile(path.str());
	for (YAML::iterator it = yaml_map.begin(); it != yaml_map.end(); ++it) {
        std::pair<std::string, int> texture = it->as<std::pair<std::string, int>>();
        SkinType skin = (SkinType) texture.second;
        this->skins[skin] = new SdlTexture(renderer, texture.first, NEGRO.r, NEGRO.g, NEGRO.b);
    }
}



bool isInVector(std::vector<uint8_t> vector, uint8_t element) {
    int max = (int) vector.size();
    int i = 0;
    bool foundIt = false;
    while (i < max && !foundIt) {
        foundIt = (vector[i] == element);
        i++;
    }
    return foundIt;
}

void selectDistinct(std::vector<TileInfo> tiles, std::vector<uint8_t>& distinctTiles) {
    for (TileInfo tile : tiles) {
        if (!isInVector(distinctTiles, tile.id)) {
            distinctTiles.push_back(tile.id);
        }
    }
}

void TextureManager::loadTiles(SdlRenderer& renderer, std::vector<TileInfo> tiles){
    std::vector<uint8_t> distinctTiles;
    TextureMap textureMap;

    selectDistinct(tiles, distinctTiles);
    
    for (uint8_t tile : distinctTiles) {
        this->tiles[tile] = new SdlTexture(renderer, textureMap[tile].texturePath); 
    }
}


TextureManager::~TextureManager(){
    if (!this->weaponsOnFloor.empty()) {
        for(auto it = this->weaponsOnFloor.begin(); it != this->weaponsOnFloor.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponsOnFloor.clear();
    }

    if (!this->weaponsOnPj.empty()) {
        for(auto it = this->weaponsOnPj.begin(); it != this->weaponsOnPj.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponsOnPj.clear();
    }

    if (!this->tiles.empty()) {
        for(auto it = this->tiles.begin(); it != this->tiles.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->tiles.clear();
    }

    if (!this->weaponsOnHud.empty()) {
        for(auto it = this->weaponsOnHud.begin(); it != this->weaponsOnHud.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponsOnHud.clear();
    }

    if (!this->animWeaponOnPj.empty()) {
        for(auto it = this->animWeaponOnPj.begin(); it != this->animWeaponOnPj.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->animWeaponOnPj.clear();
    }

    if (!this->skins.empty()) {
        for(auto it = this->skins.begin(); it != this->skins.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->skins.clear();
    }

}

SdlTexture* TextureManager::getWeaponOnHud(WeaponType weapon){
    if (weapon == KNIFE) printf("No tiene el cuchillo WeaponOnHud\n");
    return (this->weaponsOnHud[weapon]);
}
SdlTexture* TextureManager::getWeaponOnPj(WeaponType weapon){return (this->weaponsOnPj[weapon]);}
SdlTexture* TextureManager::getWeaponOnFloor(WeaponType weapon){return (this->weaponsOnFloor[weapon]);}
SdlTexture* TextureManager::getWeaponAnim(WeaponType weapon){return (this->animWeaponOnPj[weapon]);}
SdlTexture* TextureManager::getSkin(SkinType skin){return (this->skins[skin]);}
SdlTexture* TextureManager::getTiles(uint8_t tile){return (this->tiles[tile]);}