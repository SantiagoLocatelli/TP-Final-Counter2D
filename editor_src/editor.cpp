#include "editor.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>
#include <memory>
#include <utility>
#define TEXTURE_PATH "../../common_src/maps/textures.yaml"
#define TILE_WIDTH 80
#define TILE_HEIGHT 80
#define LEVEL_WIDTH 1280

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

Editor::Editor(std::vector<std::shared_ptr<SdlTexture>>& textures, TextureMap& m, std::vector<int>& mapSize, 
std::map<std::string, std::shared_ptr<Draggable>>& bombSites,
std::map<std::string, std::shared_ptr<Draggable>>& spawnSites,
int screenW, int screenH) : Presenter(mapSize, bombSites, spawnSites, screenW, screenH), map(m){
    this->textures = textures;
    this->currentType = 0;
    this->renderBombSites = false;
    this->renderSpawnSites = false;
}

void Editor::handleEvents(SDL_Event* event, SdlRenderer& renderer){
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
                currentType = this->map.size() - 1;
            }
        }else if (event->wheel.y < 0){
            //Scroll through tiles
            currentType++;
            if (currentType > this->map.size() - 1){
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
    //Mouse offsets
    SDL_Rect camera = Presenter::getCameraBox();
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Adjust to camera
    x += camera.x;
    y += camera.y;

    int textureX = 0, textureY = 0;

	for (int i = 0; i < textures.size(); i++){
        //If the mouse is inside the tile
        if ((x > textureX) && (x < textureX + TILE_WIDTH) && (y > textureY) && (y < textureY + TILE_HEIGHT)){
            //Get rid of old tile
			textures.erase(textures.begin() + i);
            std::unique_ptr<SdlTexture> texture(new SdlTexture(renderer, map[this->currentType], currentType));
			textures.insert(textures.begin() + i, std::move(texture));
			break;
        }
        //Move to next tile spot
        textureX += TILE_WIDTH;

        //If we've gone too far
        if (textureX >= this->mapSize[0]){
            //Move back
            textureX = 0;

            //Move to the next row
            textureY += TILE_HEIGHT;
        }
    }
}

void Editor::render(){
    int x = 0, y = 0;
    SDL_Rect camera = Presenter::getCameraBox();
    for (auto &texture : this->textures){
        texture->render(x - camera.x, y - camera.y, TILE_WIDTH, TILE_HEIGHT);
        
        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if (x >= this->mapSize[0]{
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }
    if (renderBombSites){
        Presenter::renderBombSites();
    }
    if (renderSpawnSites){
        Presenter::renderSpawnSites();
    }
}

std::string Editor::getTitle(){
    return this->map[this->currentType];
}

void Editor::createMap(SdlRenderer& renderer){
    for (int i = 0; i < 192; i++){
        this->textures.emplace_back(new SdlTexture(renderer, this->map[0], 0));
    }
}