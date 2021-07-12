#ifndef __EDITOR_H__
#define __EDITOR_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "MenueManager.h"
#include "presenter.h"
class Editor : public Presenter{
    private:
        bool renderBombSites;

        bool renderSpawnSites;

        bool changeScene;

    public:
        Editor(MenueManager& m, int screenW, int screenH);
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        void render() override;
        void put_tile(SdlRenderer& renderer);
        std::string getTitle() override;
        void createMap(SdlRenderer& renderer);
        bool finish() override;

        void presentBombSites();
        void stopPresentingBombSites();

        void presentSpawnSites();
        void stopPresentingSpawnSites();
};
#endif
