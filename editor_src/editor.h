#ifndef __EDITOR_H__
#define __EDITOR_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "../Sdl/sdl_texture.h"
#include "../Sdl/sdl_renderer.h"
#include "../Sdl/sdl_window.h"
#include "TextureMap.h"
class Editor{
    private:
        TextureMap map;
        std::vector<std::unique_ptr<SdlTexture>> textures;
        SDL_Rect bombSiteA, bombSiteB;
        SDL_Rect spawnSiteT, spawnSiteCT;
        int currentType;
        std::string mapID;
    public:
        Editor(const std::string path, SdlRenderer& renderer);
        void handleEvents(SDL_Event* event);
        void put_tile(SDL_Rect camera, SdlRenderer& renderer);
        void saveMap(std::string& path, std::vector<std::unique_ptr<SdlTexture>>& textures);
        std::string getTitle();
        void saveMap();
        void render(SDL_Rect camera);
        std::vector<SDL_Rect> getBombSite();
        std::vector<SDL_Rect> getSpawnSite();
        void setBombSite(std::vector<SDL_Rect> rect);
        void setSpawnSite(std::vector<SDL_Rect> rect);
        void createMap(SdlRenderer& renderer);
};
#endif
