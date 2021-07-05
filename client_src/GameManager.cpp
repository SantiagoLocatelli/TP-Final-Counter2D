#include "GameManager.h"
#include "Events/gameMath.h"

#define PIXELS_PER_METER 100
#define YOU 0


#define BOX 1
#define BACKGROUND 0

GameManager::GameManager(MapInfo map, ModelInfo model)
    : model(model){


    this->level.width = map.length*PIXELS_PER_METER;
    this->level.height = map.height*PIXELS_PER_METER;
    this->level.w_meters = map.length;
    this->level.h_meters = map.height;
    this->level.boxes = map.boxes;

    this->initializeGame(model);
}



void GameManager::initializeGame(ModelInfo model){
    SdlTexture backg(renderer, "../../common_src/img/bg.png");
    this->textures.push_back(std::move(backg));
    SdlTexture boxTexture(renderer, "../../common_src/img/green_crate.bmp");
    this->textures.push_back(std::move(boxTexture));
    
    this->addPlayer(PATH_TEXTURE, NEGRO);

    for (int i = YOU+1; i < model.players.size()+1; i++) {
        this->addPlayer(PATH_TEXTURE, NEGRO);
    }

    this->loadWeapons();

    this->update(model);
}

void GameManager::update(ModelInfo model){

    this->model = model;
    
    this->players[YOU].update(model.you, this->level, model.you.health, model.you.ammo);

    int i = YOU+1;
    for (auto it = this->model.players.begin(); it != this->model.players.end(); it++){
        
        this->players[i].update(*it, this->level);
        i++;
    }

    this->cam.centerCamera(this->players[YOU].getRect());
    this->cam.keepInBounds(level.width, level.height);
    this->stencil.setPosition(model.you, this->level);
}