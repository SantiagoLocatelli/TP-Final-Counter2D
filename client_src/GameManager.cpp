#include "GameManager.h"

#define PIXELS_PER_METER 100
#define YOU 0
#define PATH_TEXTURE "../../common_src/img/players/ct1.bmp"
const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
#define BOX 1
#define BACKGROUND 0

// cppcheck-suppress uninitMemberVar
GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h)
    :window("Counter-Strike 2D", window_w, window_h),renderer(&window), model(model), cam(window_w, window_h),
    stencil(this->renderer, window_w, window_h), pjTexture(this->renderer, PATH_TEXTURE, NEGRO.r, NEGRO.g, NEGRO.b){

    this->level.width = map.length*PIXELS_PER_METER;
    this->level.height = map.height*PIXELS_PER_METER;
    this->level.w_meters = map.length;
    this->level.h_meters = map.height;
    this->level.boxes = map.boxes;
    

    this->initializeGame(model);
}

// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameManager::renderBoxes(int camX, int camY) {
    for(auto it = this->level.boxes.begin(); it != this->level.boxes.end(); it++){
        this->textures[BOX].render(it->x*PIXELS_PER_METER - camX, it->y*PIXELS_PER_METER - camY, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameManager::renderPlayers(int camX, int camY) {
    for (auto it = this->players.begin(); it != this->players.end(); it++) {
        if (!it->isDead()){
            it->render(camX, camY);
        }
    }
}


void GameManager::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    this->textures[BACKGROUND].render(0, 0, level.width, level.height);
    int camX = this->cam.getPosX();
    int camY = this->cam.getPosY();
    renderBoxes(camX, camY);
    renderPlayers(camX, camY);
    if (!this->players[YOU].isDead()) {

        this->stencil.render(camX, camY);
    }

    renderer.updateScreen();
}


int GameManager::getRelativePlayerPosX(){return this->players[YOU].getPosX() - this->cam.getPosX();}
int GameManager::getRelativePlayerPosY(){return this->players[YOU].getPosY() - this->cam.getPosY();}

void GameManager::addPlayer(const char* pathTexture, struct Color color){
    
    Character pj(PIXELS_PER_METER, PIXELS_PER_METER, this->pjTexture);
    this->players.push_back(std::move(pj));
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