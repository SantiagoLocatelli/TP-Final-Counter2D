#ifndef __GAME_OBJECT_FACTORY_H__
#define __GAME_OBJECT_FACTORY_H__
#include "TextureMap.h"
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_renderer.h"
#include <memory>
#include <vector>
class TextureFactory{
    public:
        void unmarshalTextures(char *yamlFile, TextureMap& map);
        void unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::unique_ptr<SdlTexture>>& textures, SdlRenderer& renderer);
        void unmarshalBombSites(const char *yamlFile, SDL_Rect& bombSiteA, SDL_Rect& bombSiteB);
        void unmarshalSpawnSites(const char *yamlFile, SDL_Rect& spawnSiteT, SDL_Rect& spawnSiteCT);
};
#endif
