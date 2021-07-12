#ifndef __TEXTURE_SCREEN_H__
#define __TEXTURE_SCREEN_H__
#include "presenter.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
class TextureScreen : public Presenter{
    private:
        bool changeScene;
    public:
        TextureScreen(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        void aceptChanges() override;
        std::string getTitle() override;
        bool finish() override;

};
#endif
