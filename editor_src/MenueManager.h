#ifndef __MENUE_MANAGER_H__
#define __MENUE_MANAGER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include "TextureFactory.h"
#include "TextureMap.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/draggable.h"
class MenueManager{
    private:
        std::vector<int> mapSize;
        SdlRenderer& renderer;
        TextureMap textureMap;
        std::string mapID;
        std::list<std::unique_ptr<SdlTexture>> textures;
        std::map<std::string, std::shared_ptr<Draggable>> bombSites;
        std::map<std::string, std::shared_ptr<Draggable>> spawnSites;
        int screenWidth, screenHeight;
    public:
        MenueManager(SdlRenderer& r, const std::string path, int screenWidth, int screenHeight);
        void loadToFile();

        void renderTextures(const SDL_Rect& camera);
        void renderBombSites(const SDL_Rect& camera);
        void renderSpawnSites(const SDL_Rect& camera);
        void handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void fillSize(std::vector<SDL_Rect>& vector);
        void changeSizeOfSites(std::vector<int>& vector);
        void changeTexture(const int& type, const SDL_Rect& camera);
        void changeMapSize(const int& width, const int& height);

        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        std::string getTypeName(const int& type);
        
};
#endif
