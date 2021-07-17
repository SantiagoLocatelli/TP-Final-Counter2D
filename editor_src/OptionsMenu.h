#ifndef __OPTIONS_MENU_H__
#define __OPTIONS_MENU_H__
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <vector>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "presenter.h"
class OptionsMenu : public Presenter{
    private:
        SdlTexture backgroundTexture, widthTexture, heightTexture, save, back, quitToMenu, quit;
        std::map<std::shared_ptr<SdlTexture>, std::string> options;
        std::shared_ptr<SdlTexture> selectedTexture;
        std::vector<SdlTexture> textTexture;
        std::vector<std::shared_ptr<SdlTexture>> inputOrder;
        bool renderText;
        std::unique_ptr<SdlMixer> chunk;
        bool changeScene;

    public:
        OptionsMenu(SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        std::string getTitle() override;
        void aceptChanges() override;
        bool finish() override;
        void init();
};
#endif
