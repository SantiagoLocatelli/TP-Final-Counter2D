#include "editor.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>
#include <memory>
#include <utility>
enum helperText : int {BOMB_SITE, SPAWN_SITE, PUT_TILES, TAB, ESC, MUSIC, HIDE};

Editor::Editor(SdlRenderer& renderer, MenuManager& m, int screenW, int screenH) : Presenter(m, screenW, screenH){
    std::vector<std::string> text = {"mantenga 1 para ver los bomsites", "mantenga 2 para ver los spawnsites", "click derecho para poner las texturas",
     "aprete TAB para cambiar texturas", "aprete ESCAPE para ver opciones", "aprete 9 para pausar la musica", "aprete 3 para ocultar este texto"};
    for (unsigned int i = 0; i < text.size(); i++){
        helperMap.emplace(i, SdlTexture(renderer, FONT_PATH, FONT_SIZE, text[i], 255, 255, 255));
    }
    this->renderBombSites = false;
    this->renderSpawnSites = false;
    this->changeScene = false;
    this->hideHelper = false;
}

void Editor::render(){
    Presenter::renderTextures();
    Presenter::renderWeapons();
    if (renderBombSites){
        Presenter::renderBombSites();
    }
    if (renderSpawnSites){
        Presenter::renderSpawnSites();
    }
    if (!hideHelper){
        int posY = 0;
        std::map<int, SdlTexture>::iterator iterator = this->helperMap.begin();
        while (iterator != this->helperMap.end()){
            iterator->second.render(0,posY);
            ++iterator;
            posY += 50;
        }
    }
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
        }else if (event->key.keysym.sym == SDLK_3){
            this->hideHelper = !this->hideHelper;
        }else if (event->key.keysym.sym == SDLK_ESCAPE){
            this->changeScene = true;
        }else if (event->key.keysym.sym == SDLK_TAB){
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
    Presenter::changeTexture();
}


std::string Editor::getTitle(){
    return "Map Editor";
}

bool Editor::finish(){
    if (changeScene){
        changeScene = false;
        return true;
    }
    return false;
}
