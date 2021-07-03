#include "GameManager.h"

#define PIXELS_PER_METER 100
#define YOU 0
#define PATH_TEXTURE "../../common_src/img/players/ct1.bmp"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};
#define BOX 1
#define BACKGROUND 0

GameManager::GameManager(MapInfo map, ModelInfo model, int window_w, int window_h)
    :window("Counter-Strike 2D", window_w, window_h),renderer(&window), model(model), cam(window_w, window_h),
    stencil(this->renderer, window_w, window_h), 
    crosshair(25, 25, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b))){

    this->level.width = map.length*PIXELS_PER_METER;
    this->level.height = map.height*PIXELS_PER_METER;
    this->level.w_meters = map.length;
    this->level.h_meters = map.height;
    this->level.boxes = map.boxes;

    this->initializeGame(model);
}

void GameManager::addPlayer(const char* pathTexture, struct Color color, int index){
    SdlTexture pjTexture(this->renderer, pathTexture, color.r, color.g, color.b);
    Character pj(PIXELS_PER_METER, PIXELS_PER_METER, std::move(pjTexture)/*, this->weapons*/);
    this->players.push_back(std::move(pj));
}


void GameManager::loadWeapons(){
    // SdlTexture knife(renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // this->weapons.addWeapon(std::move(knife));
    // this->weapons.push_back(knife);
    // SdlTexture glock(renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // this->weapons.addWeapon(std::move(glock));
    // this->weapons.push_back(glock);
    // SdlTexture ak47(renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // this->weapons.addWeapon(std::move(ak47));
    // this->weapons.push_back(ak47);
    // SdlTexture awp(renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // this->weapons.addWeapon(std::move(awp));
    // this->weapons.push_back(awp);

}

void GameManager::initializeGame(ModelInfo model){
    SDL_ShowCursor(SDL_DISABLE);
    SdlTexture backg(renderer, "../../common_src/img/bg.png");
    this->textures.push_back(std::move(backg));
    SdlTexture boxTexture(renderer, "../../common_src/img/green_crate.bmp");
    this->textures.push_back(std::move(boxTexture));
    
    // es necesario que primero que cargen las armas
    loadWeapons();
    this->addPlayer(PATH_TEXTURE, NEGRO, YOU);

    for (int i = YOU+1; i < model.players.size()+1; i++) {
        this->addPlayer(PATH_TEXTURE, NEGRO, i);
    }

    
    this->update(model);
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
        it->render(camX, camY);
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
    this->stencil.render(camX, camY);
    this->crosshair.render();

    renderer.updateScreen();
}


int GameManager::getRelativePlayerPosX(){return this->players[YOU].getPosX() - this->cam.getPosX();}
int GameManager::getRelativePlayerPosY(){return this->players[YOU].getPosY() - this->cam.getPosY();}
void GameManager::setCrossHair(int posX, int posY){
    this->crosshair.setPosition(posX, posY);
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