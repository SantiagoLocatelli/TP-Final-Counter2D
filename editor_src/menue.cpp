#include "menue.h"
#include <string>
Menue::Menue(SdlRenderer& renderer, SDL_Rect bombSiteA, SDL_Rect bombSiteB, SDL_Rect spawnSiteT, SDL_Rect spawnSiteCT){
    std::string path("../../common_src/img/digital-7.ttf");
    int size = 26;
    std::vector<SDL_Rect> aux = {bombSiteA, bombSiteB, spawnSiteT, spawnSiteCT};
    for (int i = 0; i < aux.size(); i++){
        std::string width = std::to_string(aux[i].w);
        std::string height = std::to_string(aux[i].h);
        this->options.emplace_back(new SdlTexture(renderer, path, size, width, 0, 0, 0));
        this->options.emplace_back(new SdlTexture(renderer, path, size, height, 0, 0, 0));
    }
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
            texture->render(i, 100);
            i += 100;
        }

        renderer.updateScreen();
    }
}