#include "GameManager.h"

#define PIXELS_PER_METER 100

GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h, Character pj)
    :window("Counter-Strike 2D", window_w, window_h),renderer(&window), model(model), pj(std::move(pj)), cam(window_w, window_h){
    

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
void GameManager::render(){
    renderBoxes();
    //renderPlayers();
    this->pj.render(this->cam.getPosX(), this->cam.getPosY());
}


int GameManager::getRelativePlayerPosX(){return this->pj.getPosX() - this->cam.getPosX();}
int GameManager::getRelativePlayerPosY(){return this->pj.getPosY() - this->cam.getPosY();}

void GameManager::update(ModelInfo model){

}