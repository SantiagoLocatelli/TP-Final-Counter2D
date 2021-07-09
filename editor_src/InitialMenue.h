#ifndef __INITAL_MENUE_H__
#define __INITAL_MENUE_H__
#include <SDL2/SDL.h>
#include <string>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include "presenter.h"
class InitialMenue : public Presenter{
    private:
        SdlTexture background;
        SdlTexture crearMapTexture;
        SdlTexture editarMapTexture;
        std::unique_ptr<SdlMixer> chunk;
        bool editMap;
        bool createMap;
    public:
        InitialMenue(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        void aceptChanges() override;
        std::string getTitle() override;
        bool finish();

};
#endif
