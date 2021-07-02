#ifndef __EDITOR_H__
#define __EDITOR_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/draggable.h"
#include "menue.h"
#include "TextureMap.h"
class Editor{
    private:
        TextureMap map;
        std::vector<std::unique_ptr<SdlTexture>> textures;
        SDL_Rect bombSiteA, bombSiteB;
        SDL_Rect spawnSiteT, spawnSiteCT;
        int currentType;
        std::string mapID;

        std::unique_ptr<Menue> menue;
    public:
        Editor(const std::string path, SdlRenderer& renderer);
        void handleEvents(SDL_Event* event);
        void put_tile(SDL_Rect camera, SdlRenderer& renderer);
        void saveMap(std::string& path, std::vector<std::unique_ptr<SdlTexture>>& textures);
        std::string getTitle();
        void saveMap();
        void render(SDL_Rect camera);
        void createMap(SdlRenderer& renderer);
        void getBombSites(std::unique_ptr<Draggable>& siteA, std::unique_ptr<Draggable>& siteB, SdlRenderer& renderer);
        void getSpawnSites(std::unique_ptr<Draggable>& siteT, std::unique_ptr<Draggable>& siteCT, SdlRenderer& renderer);
        void changeBombSites(std::unique_ptr<Draggable>& siteA, std::unique_ptr<Draggable>& siteB);
        void changeSpawnSites(std::unique_ptr<Draggable>& siteT, std::unique_ptr<Draggable>& siteCT);

        void initMenue();
};
#endif
