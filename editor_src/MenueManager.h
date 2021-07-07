#ifndef __MENUE_MANAGER_H__
#define __MENUE_MANAGER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "editor.h"
#include "OptionsMenue.h"
#include "TextureFactory.h"
#include "TextureMap.h"
class MenueManager{
    private:
        SdlRenderer& renderer;
        TextureMap map;
        std::string mapID;
        std::vector<std::shared_ptr<SdlTexture>> textures;
        std::map<std::string, std::shared_ptr<Draggable>> bombSites;
        std::map<std::string, std::shared_ptr<Draggable>> spawnSites;
        int screenWidth, screenHeight;
    public:
        MenueManager(SdlRenderer& r, const std::string path, int screenWidth, int screenHeight);
        std::unique_ptr<Presenter> createEditor();
        std::unique_ptr<Presenter> createOptionsMenue();
        void loadToFile();
};
#endif
