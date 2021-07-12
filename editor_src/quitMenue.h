#ifndef __QUIT_MENUE_H__
#define __QUIT_MENUE_H__
#include "presenter.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include <string>
class QuitMenue : public Presenter{
    private:
        bool changeScene;
        bool& quit;
        std::unique_ptr<SdlMixer> chunk;
        SdlTexture backGround, questionTexture, cancel, saveAndQuit, quitWithoutSaving;

    
    public:
        QuitMenue(bool& quit, SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        std::string getTitle() override;
        bool finish() override;

};
#endif
