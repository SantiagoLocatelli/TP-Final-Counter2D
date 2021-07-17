#include "quitMenu.h"
#include <stdio.h>
#define FONT_SIZE 26
#define FONT_PATH "../../common_src/img/digital-7.ttf"
#define BACK_GROUND "../../common_src/img/saveBackGround.png"
#define CHUNK_PATH "../../common_src/sound/pressButton.mp3"
QuitMenu::QuitMenu(bool& q, SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH), quit(q),
backGround(renderer, BACK_GROUND), questionTexture(renderer, FONT_PATH, FONT_SIZE, "Tenes cambios sin guardar, Estas seguro que queres salir?", 255, 255, 255),
cancel(renderer, FONT_PATH, FONT_SIZE, "Cancelar", 255, 255, 255), saveAndQuit(renderer, FONT_PATH, FONT_SIZE, "Guardar y salir", 255, 255, 255),
quitWithoutSaving(renderer, FONT_PATH, FONT_SIZE, "Salir sin guardar", 255, 255, 255){
    std::vector<std::string> vec = {CHUNK_PATH};
    this->chunk = std::unique_ptr<SdlMixer>(new SdlMixer(vec));
    backGround.setBlendMode(SDL_BLENDMODE_BLEND);
    backGround.setAlpha(100);
    this->quit = quit;
    this->changeScene = false;
}

void QuitMenu::render(){
    SDL_Rect screen = Presenter::getCameraBox();
    Presenter::renderTextures();
    backGround.render(0, 0, screen.w, screen.h);
    questionTexture.render(0, 100);
    cancel.render(50, 200);
    saveAndQuit.render(200, 200);
    quitWithoutSaving.render(400, 200);

}

void QuitMenu::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            if (cancel.isMouseTouching(50, 200)){
                this->chunk->playChunk(0);
                this->changeScene = true;
            }else if (saveAndQuit.isMouseTouching(200, 200)){
                this->chunk->playChunk(0);
                Presenter::saveMap();
                this->quit = true;
            }else if (quitWithoutSaving.isMouseTouching(400, 200)){
                this->chunk->playChunk(0);
                this->quit = true;
            }
        }else if (event->key.keysym.sym == SDLK_ESCAPE){
            this->changeScene = true;
        }
        }
}

std::string QuitMenu::getTitle(){
    return "Want to quit?";
}

bool QuitMenu::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}