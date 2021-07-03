#ifndef __EDITOR_H__
#define __EDITOR_H__
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "TextureMap.h"
#include "presenter.h"
class Editor : public Presenter{
    private:
        TextureMap map;
        std::vector<std::unique_ptr<SdlTexture>> textures;
        int currentType;

        bool renderBombSites;

        bool renderSpawnSites;

    public:
        Editor(const std::string path, SdlRenderer& renderer, int screenW, int screenH);
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        void render() override;
        void put_tile(SdlRenderer& renderer);
        void saveMap(std::string& path, std::vector<std::unique_ptr<SdlTexture>>& textures);
        std::string getTitle() override;
        void saveMap() override;
        void createMap(SdlRenderer& renderer);

        void presentBombSites();
        void stopPresentingBombSites();

        void presentSpawnSites();
        void stopPresentingSpawnSites();
};
#endif
