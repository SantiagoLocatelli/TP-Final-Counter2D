#include "GameViewer.h"

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_TEXTURE "../../common_src/img/players/ct1.bmp"

struct Color {
    uint8_t r, g, b;
};

const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};

GameViewer::GameViewer(int window_w, int window_h):window(WINDOW_LABEL, window_w, window_h),
    renderer(&window), cam(window_w, window_h),
    crosshair(25, 25, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b))),
    stencil(this->renderer, window_w, window_h),
    pjTexture(this->renderer, PATH_TEXTURE, NEGRO.r, NEGRO.g, NEGRO.b), bullet(renderer){}


GameViewer::~GameViewer(){
    for(auto it = this->weaponsOnFloor.begin(); it != this->weaponsOnFloor.end(); it++) {
        SdlTexture* aux = it->second;
        it++;
        delete aux;
    }
    this->weaponsOnFloor.clear();
}




void GameViewer::addPlayer(const char* pathTexture, struct Color color){
    
    Character pj(PIXELS_PER_METER, PIXELS_PER_METER, this->pjTexture);
    this->players.push_back(std::move(pj));
}


void GameViewer::loadWeapons(){
    // SdlTexture knifeText(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // SdlTexture knifeAnim(this->renderer, "../../common_src/img/weapons/knifeslash.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // Weapon knife(std::move(knifeText), 50, 50);
    // this->weapons.push_back(std::move(knife));
    
    // SdlTexture glockText(this->renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // Weapon glock(std::move(glockText), 20, 20);
    // this->weapons.push_back(std::move(glock));
    
    // SdlTexture ak47Text(this->renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // Weapon ak47(std::move(ak47Text), 20, 20);
    // this->weapons.push_back(std::move(ak47));

    // SdlTexture awpText(this->renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // Weapon awp(std::move(awpText), 20, 20);
    // this->weapons.push_back(std::move(awp));

    this->weaponsOnFloor[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[GOD_GUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
}


// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderBoxes(int camX, int camY) {
    for(auto it = this->level.boxes.begin(); it != this->level.boxes.end(); it++){
        this->textures[BOX].render(it->x*PIXELS_PER_METER - camX, it->y*PIXELS_PER_METER - camY, PIXELS_PER_METER, PIXELS_PER_METER);
    }
}

// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderPlayers(int camX, int camY) {
    for (auto it = this->players.begin(); it != this->players.end(); it++) {
        if (!it->isDead()){
            it->render(camX, camY);
        }
    }
}

void GameViewer::renderShots(int camX, int camY){
    for(auto it = this->model.bullets.begin(); it != this->model.bullets.end(); it++){
        this->bullet.setTrajectory(this->level, *it, camX, camY);
        this->bullet.render();
    }
}

void GameViewer::renderWeapons(int camX, int camY){
    for(auto it = this->model.drops.begin(); it != this->model.drops.end(); it++) {
        printf("dentro del for de render weapons\n");
        int posX = Math::ruleOfThree(it->pos.x, this->level.w_meters, this->level.width) - camX;
        int posY = Math::ruleOfThree(it->pos.y, this->level.h_meters, this->level.height) - camY;
        this->weaponsOnFloor[it->type]->render(posX, posY, 50, 50);
    }
}


void GameViewer::render(){

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
    this->crosshair.render();
    renderShots(camX, camY);
    renderWeapons(camX, camY);

    renderer.updateScreen();
}


int GameViewer::getRelativePlayerPosX(){return this->players[YOU].getPosX() - this->cam.getPosX();}
int GameViewer::getRelativePlayerPosY(){return this->players[YOU].getPosY() - this->cam.getPosY();}

void GameViewer::setCrossHair(int posX, int posY){
    this->crosshair.setPosition(posX, posY);
}