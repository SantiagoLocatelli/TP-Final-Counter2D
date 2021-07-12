#include "textureScreen.h"

TextureScreen::TextureScreen(SdlRenderer& renderer, MenueManager& m ,int screenW, int screenH) : Presenter(m, screenW, screenH){
    this->changeScene = false;
}

void TextureScreen::render(){
    Presenter::renderMapTextures();
}

void TextureScreen::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    if (event->type == SDL_KEYDOWN){
        if (event->key.keysym.sym == SDLK_TAB){
            this->changeScene = true;
        }
    }else{
        Presenter::handleSelectTexture(event);
    }
}
void TextureScreen::aceptChanges(){}

std::string TextureScreen::getTitle(){
    return "Select Texture";
}

bool TextureScreen::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}