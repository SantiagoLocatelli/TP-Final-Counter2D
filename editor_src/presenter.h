#ifndef __PRESENTER_H__
#define __PRESENTER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <map>
#include <vector>
#include "../client_src/Character/camera.h"
#include "MenueManager.h"
class Presenter{
    private:
        MenueManager& menueManager;

        Camera camera;
    public:
        Presenter(MenueManager& menueManager, int screenW, int screenH);
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
        void needToSave();
        void saveMap();
        void goToMenue();

        SDL_Rect getCameraBox();
        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        int getTileSize();
};
#endif
