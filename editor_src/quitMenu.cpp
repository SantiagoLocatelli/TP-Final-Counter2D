#include "quitMenu.h"
#include <stdio.h>
#define FONT_PATH "/usr/local/share/counter2d/resources/common/img/digital-7.ttf"
#define BACK_GROUND "/usr/local/share/counter2d/resources/common/img/saveBackGround.png"
#define CHUNK_PATH "/usr/local/share/counter2d/resources/common/sound/pressButton.mp3"
enum keyForMap : int {QUESTION, CANCEL, SAVE_AND_QUIT, QUIT_NO_SAVE};

QuitMenu::QuitMenu(bool& q, SdlRenderer& renderer, MenuManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH), quit(q),
backGround(renderer, BACK_GROUND){
    std::vector<std::string> text = {"Tenes cambios sin guardar, Estas seguro que queres salir?", "Cancelar", "Guardar y salir", "Salir sin guardar"};
    for (unsigned int i = 0; i < text.size(); i++){
        menuTextures.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, text[i], 255, 255, 255));
    }
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
    menuTextures.at(QUESTION).render((screen.w - menuTextures.at(QUESTION).getWidth())/2, 100);
    menuTextures.at(CANCEL).render((screen.w - menuTextures.at(CANCEL).getWidth() - menuTextures.at(QUESTION).getWidth())/2, 200);
    menuTextures.at(SAVE_AND_QUIT).render((screen.w - menuTextures.at(SAVE_AND_QUIT).getWidth())/2, 200);
    menuTextures.at(QUIT_NO_SAVE).render((screen.w - menuTextures.at(SAVE_AND_QUIT).getWidth() + menuTextures.at(QUESTION).getWidth())/2, 200);
}

void QuitMenu::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    if (event->type == SDL_MOUSEBUTTONDOWN){
        if (event->button.button == SDL_BUTTON_LEFT){
            SDL_Rect screen = Presenter::getCameraBox();
            if (menuTextures.at(CANCEL).isMouseTouching((screen.w - menuTextures.at(CANCEL).getWidth() - menuTextures.at(QUESTION).getWidth())/2, 200)){
                this->chunk->playChunk(0);
                this->changeScene = true;
            }else if (menuTextures.at(SAVE_AND_QUIT).isMouseTouching((screen.w - menuTextures.at(SAVE_AND_QUIT).getWidth())/2, 200)){
                this->chunk->playChunk(0);
                Presenter::saveMap();
                this->quit = true;
            }else if (menuTextures.at(QUIT_NO_SAVE).isMouseTouching(screen.w/2 - menuTextures.at(SAVE_AND_QUIT).getWidth()/2 + menuTextures.at(QUESTION).getWidth()/2, 200)){
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