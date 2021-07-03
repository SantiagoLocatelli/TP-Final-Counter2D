#ifndef __PRESENTER_H__
#define __PRESENTER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <map>
#include <vector>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/draggable.h"
#include "../client_src/Character/camera.h"
class Presenter{
    private:
        std::string mapID;

        std::map<std::string, std::unique_ptr<Draggable>> bombSites;

        std::map<std::string, std::unique_ptr<Draggable>> spawnSites;

        Camera camera;
    public:
        Presenter(const std::string path, SdlRenderer& r, int screenW, int screenH);
        virtual void render() = 0;
        virtual void handleEvents(SDL_Event* event, SdlRenderer& renderer) = 0;
        virtual std::string getTitle() = 0;
        void renderBombSites();
        void renderSpawnSites();
        void centerCamera();
        virtual void saveMap(){};
        void loadToFile(std::vector<std::unique_ptr<SdlTexture>>& textures);
        SDL_Rect getCameraBox();
        void handleBombSitesEvent(SDL_Event* event);
        void handleSpawnSitesEvent(SDL_Event* event);
        void fillSize(std::vector<SDL_Rect>& vector);
};
#endif
