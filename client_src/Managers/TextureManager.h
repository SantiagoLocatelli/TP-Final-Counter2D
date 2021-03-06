#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/TextureMap.h"
#include "../common_src/Utils.h"
#include "LevelInfo.h"
#include <vector>
#include <map>



class TextureManager{
private:

    SdlTexture* explosion;
    std::map<SkinType, SdlTexture*> skins;
    std::map<WeaponType, SdlTexture*> weaponsOnPj;
    std::map<WeaponType, SdlTexture*> animWeaponOnPj;
    std::map<WeaponType, SdlTexture*> weaponsOnFloor;
    std::map<WeaponType, SdlTexture*> weaponsOnHud;
    std::map<uint8_t, SdlTexture*> tiles;
    std::map<uint8_t, TextureInfo> tilesInfo;

    void loadTiles(SdlRenderer& renderer, std::vector<TileInfo> tiles);
    void loadTexturesWeapons(SdlRenderer& renderer);
    void loadWeaponsOnPlayer(SdlRenderer& renderer);
    void loadWeaponsOnFloor(SdlRenderer& renderer);
    void loadWeaponsOnHud(SdlRenderer& renderer);
    void loadWeaponsAnim(SdlRenderer& renderer);
    void loadSkins(SdlRenderer& renderer);

public:

    TextureManager(SdlRenderer& renderer, std::vector<TileInfo> tiles);
    ~TextureManager();

    SdlTexture* getExplosionAnim();
    SdlTexture* getWeaponOnHud(WeaponType weapon);
    SdlTexture* getWeaponOnPj(WeaponType weapon);
    SdlTexture* getWeaponOnFloor(WeaponType weapon);
    SdlTexture* getWeaponAnim(WeaponType weapon);
    SdlTexture* getSkin(SkinType skin);
    SdlTexture* getTiles(uint8_t tile);
    TextureInfo getTileInfo(uint8_t tileInfo);
};

#endif