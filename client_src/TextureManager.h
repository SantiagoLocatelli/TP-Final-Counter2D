#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/TextureMap.h"
#include "../common_src/WeaponType.h"
#include <vector>
#include <map>

enum SkinType : int {CT1, CT2, CT3, CT4, TT1, TT2, TT3, TT4};

struct Color {
    uint8_t r,g,b;
};

class TextureManager{
private:

    std::map<SkinType, SdlTexture*> skins;
    std::map<WeaponType, SdlTexture*> weaponOnPj;
    std::map<WeaponType, SdlTexture*> animWeaponOnPj;
    std::map<WeaponType, SdlTexture*> weaponsOnFloor;
    std::map<WeaponType, SdlTexture*> weaponOnHud;
    std::map<uint8_t, SdlTexture*> tiles;

    void loadTiles(SdlRenderer& renderer, std::vector<TileInfo> tiles);
    void loadTexturesWeapons(SdlRenderer& renderer);
    void loadSkins(SdlRenderer& renderer);

public:

    TextureManager(SdlRenderer& renderer, std::vector<TileInfo> tiles);
    ~TextureManager();
};

#endif