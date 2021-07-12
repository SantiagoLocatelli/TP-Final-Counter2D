#ifndef __OPTIONS_MENUE_H__
#define __OPTIONS_MENUE_H__
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <vector>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "presenter.h"
class OptionsMenue : public Presenter{
    private:
        SdlTexture backgroundTexture;
        SdlTexture widthTexture;
        SdlTexture heightTexture;
        std::map<std::shared_ptr<SdlTexture>, std::string> options;
        std::shared_ptr<SdlTexture> selectedTexture;
        std::vector<SdlTexture> textTexture;
        std::vector<std::shared_ptr<SdlTexture>> inputOrder;
        bool renderText;
        std::unique_ptr<SdlMixer> chunk;
        bool changeScene;

    public:
        OptionsMenue(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        std::string getTitle() override;
        void aceptChanges() override;
        bool finish() override;
        void init();
};
#endif
