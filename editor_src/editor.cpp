#include "editor.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>
#include <memory>
#include <utility>
#define TEXTURE_PATH "../../common_src/maps/textures.yaml"


Editor::Editor(MenueManager& m, int screenW, int screenH) : Presenter(m, screenW, screenH){
    this->currentType = 0;
    this->renderBombSites = false;
    this->renderSpawnSites = false;
    this->changeScene = false;
}

void Editor::handleEvents(SDL_Event* event, SdlRenderer& renderer){
    Presenter::centerCamera();
    if (event->type == SDL_MOUSEBUTTONDOWN){
        //On left mouse click
        if (event->button.button == SDL_BUTTON_RIGHT){
            put_tile(renderer);
        }
    //Manage key downs events
    }else if (event->type == SDL_KEYDOWN){
        //bombsites
        if (event->key.keysym.sym == SDLK_1){
            presentBombSites();
        //spawnsites
        }else if (event->key.keysym.sym == SDLK_2){
            presentSpawnSites();
        }else if (event->key.keysym.sym == SDLK_ESCAPE){
            this->changeScene = true;
        }
        //Manage key ups events
    }else if (event->type == SDL_KEYUP){
        //bombsites
        if (event->key.keysym.sym == SDLK_1){
            stopPresentingBombSites();
        //spawnsites
        }else if (event->key.keysym.sym == SDLK_2){
            stopPresentingSpawnSites();
        }
    }else if (event->type == SDL_MOUSEWHEEL){
        //On mouse wheel scroll
        if (event->wheel.y > 0){
            //Scroll through tiles
            currentType--;
            if (currentType < 0){
                currentType = Presenter::getTextureMapSize() - 1;
            }
        }else if (event->wheel.y < 0){
            //Scroll through tiles
            currentType++;
            if (currentType >= Presenter::getTextureMapSize() - 1){
                currentType = 0;
            }
        }
    }

    if (renderBombSites){
        Presenter::handleBombSitesEvent(event);
    }

    if (renderSpawnSites){
        Presenter::handleSpawnSitesEvent(event);
    }
}

void Editor::presentBombSites(){
    this->renderBombSites = true;
}

void Editor::stopPresentingBombSites(){
    this->renderBombSites = false;
}

void Editor::presentSpawnSites(){
    this->renderSpawnSites = true;
}

void Editor::stopPresentingSpawnSites(){
    this->renderSpawnSites = false;
}

void Editor::put_tile(SdlRenderer& renderer){
    Presenter::changeTexture(currentType);
}

void Editor::render(){
    Presenter::renderTextures();
    if (renderBombSites){
        Presenter::renderBombSites();
    }
    if (renderSpawnSites){
        Presenter::renderSpawnSites();
    }
}

std::string Editor::getTitle(){
    return Presenter::getTypeName(currentType);
}

bool Editor::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}
