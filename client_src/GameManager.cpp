#include "GameManager.h"

#define PIXELS_PER_METER 100
#define YOU 0
#define PATH_TEXTURE "../common_src/img/players/ct1.bmp"
const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
#define BOX 1
#define BACKGROUND 0

// cppcheck-suppress uninitMemberVar
GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h)
    :window("Counter-Strike 2D", window_w, window_h),renderer(&window), model(model), cam(window_w, window_h),
    stencil(this->renderer, window_w, window_h){

    this->level.width = map.length*PIXELS_PER_METER;
    this->level.height = map.height*PIXELS_PER_METER;
    this->level.w_meters = map.length;
    this->level.h_meters = map.height;
    this->level.boxes = map.boxes;


    this->initializeGame(model);
}

// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameManager::renderBoxes() {
    for(auto it = this->level.boxes.begin(); it != this->level.boxes.end(); it++){
        this->textures[BOX].render(it->x*PIXELS_PER_METER - this->cam.getPosX(), it->y*PIXELS_PER_METER - this->cam.getPosY(), PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

// // ESTO EN LA VERSION FINAL NO TIENE QUE IR
// void GameManager::renderPlayers() {
//     printf("cantidad de jugadores: %i\n", model.players.size());
//     for(auto it = this->model.players.begin(); it != this->model.players.end(); it++) {
//         this->playerTexture.render(it->x - this->cam.getPosX(), it->y - this->cam.getPosY(), PIXELS_PER_METER, PIXELS_PER_METER, it->angle);
//     }
// }



void GameManager::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->textures[BACKGROUND].render(0, 0, level.width, level.height);
    renderBoxes();
    //renderPlayers();
    int camX = this->cam.getPosX();
    int camY = this->cam.getPosY();
    this->stencil.render(camX, camY);
    for (auto it = this->players.begin(); it != this->players.end(); it++) {
        it->render(camX, camY);
    }

    renderer.updateScreen();
}


// int GameManager::getRelativePlayerPosX(){return this->pj.getPosX() - this->cam.getPosX();}
// int GameManager::getRelativePlayerPosY(){return this->pj.getPosY() - this->cam.getPosY();}

void GameManager::addPlayer(const char* pathTexture, struct Color color, int index){
    SdlTexture pjTexture(this->renderer, pathTexture, color.r, color.g, color.b);
    Character pj(PIXELS_PER_METER, PIXELS_PER_METER, std::move(pjTexture));
    this->players.push_back(std::move(pj));
}

void GameManager::initializeGame(ModelInfo model){
    SdlTexture backg(renderer, "../common_src/img/bg.png");
    this->textures.push_back(std::move(backg));
    SdlTexture boxTexture(renderer, "../common_src/img/green_crate.bmp");
    this->textures.push_back(std::move(boxTexture));
    
    this->addPlayer(PATH_TEXTURE, NEGRO, YOU);

    for (int i = YOU+1; i < model.players.size()+1; i++) {
        this->addPlayer(PATH_TEXTURE, NEGRO, i);
    }

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