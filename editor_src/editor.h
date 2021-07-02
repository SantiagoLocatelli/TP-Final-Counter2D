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
        int currentType;
        std::string mapID;

        std::map<std::string, std::unique_ptr<Draggable>> bombSites;
        bool renderBombSites;

        std::map<std::string, std::unique_ptr<Draggable>> spawnSites;
        bool renderSpawnSites;

        std::unique_ptr<Menue> menue;
    public:
        Editor(const std::string path, SdlRenderer& renderer);
        void handleEvents(SDL_Event* event, SDL_Rect camera);
        void put_tile(SDL_Rect camera, SdlRenderer& renderer);
        void saveMap(std::string& path, std::vector<std::unique_ptr<SdlTexture>>& textures);
        std::string getTitle();
        void saveMap();
        void render(SDL_Rect camera);
        void createMap(SdlRenderer& renderer);

        void initMenue();

        void presentBombSites();
        void stopPresentingBombSites();

        void presentSpawnSites();
        void stopPresentingSpawnSites();
};
#endif
