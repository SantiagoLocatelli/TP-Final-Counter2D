#ifndef __GAME_OBJECT_FACTORY_H__
#define __GAME_OBJECT_FACTORY_H__
#include "TextureMap.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/draggable.h"
#include <memory>
#include <map>
#include <vector>
#include <string>
class TextureFactory{
    public:
        void unmarshalTextures(const char *yamlFile, TextureMap& map);
        void unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::shared_ptr<SdlTexture>>& textures, SdlRenderer& renderer);
        void unmarshalBombSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer);
        void unmarshalSpawnSites(const char *yamlFile, std::map<std::string, std::shared_ptr<Draggable>>& bombSites, SdlRenderer& renderer);
};
#endif
