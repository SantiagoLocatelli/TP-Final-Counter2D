#include "GameViewer.h"

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_TEXTURE "../../common_src/img/players/ct1.bmp"
#define SIZE_CROSSHAIR 25

struct Color {
    uint8_t r, g, b;
};

const struct Color NEGRO = {0xFF, 0xFF, 0xFF};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};

GameViewer::GameViewer(int window_w, int window_h, LevelInfo level): window(WINDOW_LABEL, window_w, window_h),
    renderer(&window), 
    cam(window_w, window_h),
    pjTexture(this->renderer, PATH_TEXTURE, NEGRO.r, NEGRO.g, NEGRO.b), 
    bullet(renderer),
    mainPlayer( level.mainPlayer, pjTexture, 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window_w, window_h))){

}


GameViewer::~GameViewer(){
    for(auto it = this->weaponsOnFloor.begin(); it != this->weaponsOnFloor.end(); it++) {
        SdlTexture* aux = it->second;
        it++;
        delete aux;
    }
    this->weaponsOnFloor.clear();

    for(auto it = this->weaponOnPj.begin(); it != this->weaponOnPj.end(); it++) {
        SdlTexture* aux = it->second;
        it++;
        delete aux;
    }
    this->weaponOnPj.clear();

    for(auto it = this->textures.begin(); it != this->textures.end(); it++) {
        SdlTexture* aux = it->second;
        it++;
        delete aux;
    }
    this->textures.clear();
}




void GameViewer::loadWeapons(){

    this->weaponOnPj[KNIFE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // SdlTexture knifeAnim(this->renderer, "../../common_src/img/weapons/knifeslash.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    
    this->weaponOnPj[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    
    this->weaponOnPj[RIFLE] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);

    this->weaponOnPj[SNIPER] = new SdlTexture(this->renderer, "../../common_src/img/weapons/awp.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    // SdlTexture knife(this->renderer, "../../common_src/img/weapons/knife.bmp", NEGRO.r, NEGRO.g, NEGRO.b);

    this->weaponsOnFloor[PISTOL] = new SdlTexture(this->renderer, "../../common_src/img/weapons/glock_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
    this->weaponsOnFloor[GOD_GUN] = new SdlTexture(this->renderer, "../../common_src/img/weapons/ak47_d.bmp", NEGRO.r, NEGRO.g, NEGRO.b);
}





// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderPlayers(int camX, int camY) {

}

void GameViewer::renderShots(int camX, int camY){

}

void GameViewer::renderWeapons(int camX, int camY){

}


void GameViewer::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    int camX = this->cam.getPosX();
    int camY = this->cam.getPosY();
    
    renderBoxes(camX, camY);
    renderPlayers(camX, camY);

    //render maincharacter

    renderShots(camX, camY);
    renderWeapons(camX, camY);

    renderer.updateScreen();
}


void GameViewer::setCrossHair(Coordenada pos){
    this->mainPlayer.setCrossHair(pos);
}
Coordenada GameViewer::mainPlayerRelativePos();