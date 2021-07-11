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
        std::vector<float> mapSize;
        SdlRenderer& renderer;
        TextureMap textureMap;
        std::string mapID;
        std::list<std::unique_ptr<SdlTexture>> textures;
        std::vector<SdlTexture> textureScreen;
        std::map<std::string, std::shared_ptr<Draggable>> bombSites;
        std::map<std::string, std::shared_ptr<Draggable>> spawnSites;
        int screenWidth, screenHeight;
        int currentType;
    public:
        MenueManager(SdlRenderer& r, int screenWidth, int screenHeight);
        void loadToFile();

        void renderTextures(const SDL_Rect& camera);
        void renderBombSites(const SDL_Rect& camera);
        void renderSpawnSites(const SDL_Rect& camera);
        void renderMapTextures(const SDL_Rect& camera);
        void handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void handleSelectTexture(SDL_Event* event, const SDL_Rect& camera);
        void fillSize(std::vector<SDL_Rect>& vector);
        void changeSizeOfSites(std::vector<float>& vector);
        void changeTexture(const SDL_Rect& camera);
        void changeMapSize(const int& width, const int& height);
        void changeToMeters(std::vector<SDL_Rect>& vector);
        void createMap();
        void editMap(const std::string& mapID);

        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        std::string getTypeName(const int& type);
        int getTileSize();
        int getCurrentType();
};
#endif
