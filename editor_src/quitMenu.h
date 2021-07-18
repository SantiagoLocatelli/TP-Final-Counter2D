#ifndef __QUIT_MENU_H__
#define __QUIT_MENU_H__
#include "presenter.h"
#include <map>
#include "../common_src/Sdl/sdl_renderer.h"
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_mixer.h"
#include <string>
class QuitMenu : public Presenter{
    private:
        bool& quit;
        SdlTexture backGround;
        std::map<int, SdlTexture> menuTextures;
        bool changeScene;
        std::unique_ptr<SdlMixer> chunk;

    
    public:
        QuitMenu(bool& quit, SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH);
        void render() override;
        void handleEvents(SDL_Event* event, SdlRenderer& renderer) override;
        std::string getTitle() override;
        bool finish() override;

};
#endif
