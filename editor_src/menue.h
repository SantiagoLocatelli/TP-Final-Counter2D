#ifndef __MENUE_H__
#define __MENUE_H__
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/button.h"
#include "presenter.h"
class Menue : public Presenter{
    private:
        std::map<std::shared_ptr<SdlTexture>, std::string> options;
        std::shared_ptr<SdlTexture> selectedTexture;
        bool renderText;

    public:
        Menue(const std::string path, SdlRenderer& r, int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        std::string getTitle() override;
        void init();
};
#endif
