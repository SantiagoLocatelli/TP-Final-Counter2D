#include "menue.h"
#include <string>
#include <utility>
#include <stdio.h>
Menue::Menue(const std::string path, SdlRenderer& renderer, int screenW, int screenH) : Presenter(path, renderer, screenW, screenH){
    std::string fontPath("../../common_src/img/digital-7.ttf");
    int size = 26;
    std::vector<SDL_Rect> aux;
    Presenter::fillSize(aux);
    for (int i = 0; i < aux.size(); i++){
        std::string width = std::to_string(aux[i].w);
        std::string height = std::to_string(aux[i].h);
        this->options.emplace_back(new SdlTexture(renderer, fontPath, size, width, 0, 0, 0));
        this->options.emplace_back(new SdlTexture(renderer, fontPath, size, height, 0, 0, 0));
    }
}

void Menue::render(){
    int i = 0;
    for (auto &texture : this->options){
        texture->render(100, i);
        i += 100;
    }
}

void Menue::handleEvents(SDL_Event* event, SdlRenderer& renderer){

}

std::string Menue::getTitle(){
    return "Options Menue";
}

void Menue::init(){
    bool quit = false;
    SDL_Event event;
    SdlRenderer renderer(this->options[0]->getRenderer());
    while (!quit){
        while (SDL_PollEvent(&event) != 0){
            //User requests quit
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                }
            }
        }
        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();

        int i = 0;
        for (auto &texture : this->options){
            texture->render(100, i);
            i += 100;
        }

        renderer.updateScreen();
    }
}