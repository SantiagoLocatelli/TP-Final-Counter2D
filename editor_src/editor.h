#ifndef __EDITOR_H__
#define __EDITOR_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "MenuManager.h"
#include "presenter.h"
class Editor : public Presenter{
    private:
        std::map<int, SdlTexture> helperMap;

        bool renderBombSites, renderSpawnSites, changeScene, hideHelper;

    public:
        Editor(SdlRenderer& renderer, MenuManager& m, int screenW, int screenH);
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
