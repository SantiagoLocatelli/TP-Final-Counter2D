#ifndef __TEXTURE_SCREEN_H__
#define __TEXTURE_SCREEN_H__
#include "presenter.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_mixer.h"
class TextureScreen : public Presenter{
    private:
        bool changeScene, renderFloors, renderWalls;
        SdlTexture background, floors, walls, back, arrow;
        std::unique_ptr<SdlMixer> chunk;
        int page;
    public:
        TextureScreen(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        void aceptChanges() override;
        std::string getTitle() override;
        bool finish() override;

};
#endif
