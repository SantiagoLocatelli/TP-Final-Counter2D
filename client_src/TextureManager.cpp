#include "TextureManager.h"
#include "levelInfo.h"

#define PATH_CT1 "../../common_src/img/players/ct1.bmp"

const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};

TextureManager::TextureManager(SdlRenderer& renderer, std::vector<TileInfo> tiles){

}


void TextureManager::loadTexturesWeapons(SdlRenderer& renderer){

//enum WeaponType : char {KNIFE, PISTOL, SHOTGUN, RIFLE, SNIPER, BOMB, DEFUSER};

    this->weaponOnPj[KNIFE] = new SdlTexture(renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[PISTOL] = new SdlTexture(renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[RIFLE] = new SdlTexture(renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[SNIPER] = new SdlTexture(renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponOnPj[SHOTGUN] = new SdlTexture(renderer, "../../common_src/img/weapons/m3.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    
    // FALTA CARGAR EL EFECTO DE LAS ARMAS
    this->animWeaponOnPj[KNIFE] = new SdlTexture(renderer, "../../common_src/img/weapons/knifeslash.bmp", 0x00, 0x00, 0x00);
    //buscar un efecto de arma piola
    this->animWeaponOnPj[PISTOL] = new SdlTexture(renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[RIFLE] = new SdlTexture(renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[SNIPER] = new SdlTexture(renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);
    this->animWeaponOnPj[SHOTGUN] = new SdlTexture(renderer, "../../common_src/img/weapons/explosion.png", 0x00, 0x00, 0x00);

    this->weaponsOnFloor[PISTOL] = new SdlTexture(renderer, "../../common_src/img/weapons/glock_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[SHOTGUN] = new SdlTexture(renderer, "../../common_src/img/weapons/m3_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[SNIPER] = new SdlTexture(renderer, "../../common_src/img/weapons/awp_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[RIFLE] = new SdlTexture(renderer, "../../common_src/img/weapons/ak47_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[BOMB] = new SdlTexture(renderer, "../../common_src/img/weapons/bomb_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);

    this->weaponOnHud[PISTOL] = new SdlTexture(renderer, "../../common_src/img/weapons/glock_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[SNIPER] = new SdlTexture(renderer, "../../common_src/img/weapons/awp_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[RIFLE] = new SdlTexture(renderer, "../../common_src/img/weapons/ak47_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[SHOTGUN] = new SdlTexture(renderer, "../../common_src/img/weapons/m3_m.bmp", FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b);
    this->weaponOnHud[BOMB] = new SdlTexture(renderer, "../../common_src/img/weapons/bomb_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
}


void TextureManager::loadSkins(SdlRenderer& renderer){
    this->skins[CT] = new SdlTexture(renderer, PATH_CT1, NEGRO.r, NEGRO.g, NEGRO.b);
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

    if (!this->weaponOnPj.empty()) {
        for(auto it = this->weaponOnPj.begin(); it != this->weaponOnPj.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponOnPj.clear();
    }

    if (!this->tiles.empty()) {
        for(auto it = this->tiles.begin(); it != this->tiles.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->tiles.clear();
    }

    if (!this->weaponOnHud.empty()) {
        for(auto it = this->weaponOnHud.begin(); it != this->weaponOnHud.end(); it++) {
            SdlTexture* aux = it->second;
            delete aux;
        }
        this->weaponOnHud.clear();
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
