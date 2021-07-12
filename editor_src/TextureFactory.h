#ifndef __GAME_OBJECT_FACTORY_H__
#define __GAME_OBJECT_FACTORY_H__
#include "TextureMap.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/draggable.h"
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <string>
class TextureFactory{
    public:
        void unmarshalMap(const char *yamlFile, TextureMap& map, std::list<std::unique_ptr<SdlTexture>>& textures,
         std::vector<float>& mapSize, SdlRenderer& renderer);
        void unmarshalBombSites(const char *yamlFile, std::map<std::string, std::unique_ptr<Draggable>>& bombSites,
         SdlRenderer& renderer, const int& tile_size);
        void unmarshalSpawnSites(const char *yamlFile, std::map<std::string, std::unique_ptr<Draggable>>& bombSites,
         SdlRenderer& renderer, const int& tile_size);
};
#endif
