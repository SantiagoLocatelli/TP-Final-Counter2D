#ifndef __PRESENTER_H__
#define __PRESENTER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <map>
#include <vector>
#include "../common_src/Camera.h"
#include "MenuManager.h"
class Presenter{
    private:
        MenuManager& menuManager;

        Camera camera;
    public:
        Presenter(MenuManager& menuManager, int screenW, int screenH);
        virtual void render() = 0;
        virtual void handleEvents(SDL_Event* event, SdlRenderer& renderer) = 0;
        virtual std::string getTitle() = 0;
        virtual void aceptChanges(){};
        virtual bool finish() = 0;

        void renderTextures();
        void renderWeapons();
        void renderBombSites();
        void renderSpawnSites();
        void renderMapTextures();
        void renderMapWalls(int& page);
        void renderMapFloors(int& page);
        void renderMapWeapons(int& page);

        void handleBombSitesEvent(SDL_Event* event);
        void handleSpawnSitesEvent(SDL_Event* event);
        void handleFloorsTexture(SDL_Event* event, int& page);
        void handleWallsTexture(SDL_Event* event, int& page);
        void handleWeaponsTexture(SDL_Event* event, int& page);

        void centerCamera();
        void fillSize(std::vector<SDL_Rect>& vector);
        void changeSizeOfSites(std::vector<float>& vector);
        void changeTexture();
        void createMap(const std::string mapID);
        void editMap(const std::string& mapID);
        void putBombSites(const int numberOfBombs);
        void needToSave();
        void saveMap();
        void goToMenu();
        void quit();

        SDL_Rect getCameraBox();
        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        int getTileSize();
};
#endif
