#include "GameManager.h"

#define PIXELS_PER_METER 100

// cppcheck-suppress uninitMemberVar
GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h)
    :window("Counter-Strike 2D", window_w, window_h),renderer(&window), model(model), cam(window_w, window_h),
    stencil(this->renderer, window_w, window_h){

    this->level.width = map.length*PIXELS_PER_METER;
    this->level.height = map.height*PIXELS_PER_METER;
    this->level.w_meters = map.length;
    this->level.h_meters = map.height;
    this->level.boxes = map.boxes;
}
// // ESTO EN LA VERSION FINAL NO TIENE QUE IR
// void GameManager::renderBoxes() {
//     for(auto it = this->level.boxes.begin(); it != this->level.boxes.end(); it++){
//         this->boxTexture.render(it->x*PIXELS_PER_METER - this->cam.getPosX(), it->y*PIXELS_PER_METER - this->cam.getPosY(), PIXELS_PER_METER, PIXELS_PER_METER);
//     }
// }

// // ESTO EN LA VERSION FINAL NO TIENE QUE IR
// void GameManager::renderPlayers() {
//     printf("cantidad de jugadores: %i\n", model.players.size());
//     for(auto it = this->model.players.begin(); it != this->model.players.end(); it++) {
//         this->playerTexture.render(it->x - this->cam.getPosX(), it->y - this->cam.getPosY(), PIXELS_PER_METER, PIXELS_PER_METER, it->angle);
//     }
// }

void GameManager::addPlayer(const char* pathTexture, struct Color color){
    SdlTexture pjTexture(this->renderer, pathTexture, color.r, color.g, color.b);
    Character pj(PIXELS_PER_METER, PIXELS_PER_METER, std::move(pjTexture));
    // this->pj = std::move(pj);
}


void GameManager::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();


    // renderBoxes();
    //renderPlayers();
    int camX = this->cam.getPosX();
    int camY = this->cam.getPosY();
    // this->pj.render(camX, camY);
    this->stencil.render(camX, camY);


    renderer.updateScreen();
}


// int GameManager::getRelativePlayerPosX(){return this->pj.getPosX() - this->cam.getPosX();}
// int GameManager::getRelativePlayerPosY(){return this->pj.getPosY() - this->cam.getPosY();}

void GameManager::update(ModelInfo model){

    
    // this->stencil.setPosition();
}