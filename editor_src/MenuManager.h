#ifndef __MENU_MANAGER_H__
#define __MENU_MANAGER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include "TextureFactory.h"
#include "../common_src/TextureMap.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/draggable.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "macros.h"
class MenuManager{
    private:
        std::vector<int> mapSize;
        SdlRenderer& renderer;
        TextureMap textureMap;
        int screenWidth, screenHeight, currentType, borderType;
        std::string mapID;
        std::vector<std::unique_ptr<SdlTexture>> textures;
        std::vector<SdlTexture> floorTextureScreen, wallTextureScreen, weaponTextureScreen;
        std::map<std::string, std::unique_ptr<Draggable>> bombSites;
        std::map<std::string, std::unique_ptr<Draggable>> spawnSites;
        std::map<int, SdlTexture> weaponMap;
        std::string needsToSave;
        std::unique_ptr<SdlMixer> chunk;

        std::vector<int> weaponTypes;
        bool goToStart, isWeapon, quitEditor;
    public:
        MenuManager(SdlRenderer& r, int screenWidth, int screenHeight);
        void loadToFile();

        //RENDER
        void renderTextures(const SDL_Rect& camera);
        void renderWeapons(const SDL_Rect& camera);
        void renderBombSites(const SDL_Rect& camera);
        void renderSpawnSites(const SDL_Rect& camera);
        void renderMapFloors(int& page);
        void renderMapWalls(int& page);
        void renderMapWeapons(int& page);
        void renderMapTextures(int& page, std::vector<SdlTexture>& textures);

        //HANDLE EVENTS
        void handleBombSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void handleSpawnSitesEvent(SDL_Event* event, const SDL_Rect& camera);
        void handleSelectWall(SDL_Event* event, int& page);
        void handleSelectFloor(SDL_Event* event, int& page);
        void handleSelectWeapon(SDL_Event* event, int& page);
        void handleSelectTexture(SDL_Event* event, int& page, std::vector<SdlTexture>& textures);

        //CHANGE SIZE OF MAP
        void changeSizeOfSites(std::vector<float>& vector);
        void changeMapSize(const int& width, const int& height);
        void deleteTextureColumns(const int numberOfRows, const int rowNumber, const int newColumns);
        void deleteTextureRows(const int newRows);
        void insertTextureColumns(const int endOfRowPosition , const int newColumns);
        void insertTextureRows(const int columnsNumber);

        void fillSize(std::vector<SDL_Rect>& vector);
        void changeTexture(const SDL_Rect& camera);
        void changeToMeters(std::vector<SDL_Rect>& vector);
        void createMap(const std::string mapID);
        void editMap(const std::string& mapID);
        void needToSave();
        void goToMenu();
        void requestQuit();

        bool quitToMenu();
        bool quit();
        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        int getTileSize();
        std::string getSaveState();
};
#endif
