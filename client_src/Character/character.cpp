#include "character.h"
#include "../Events/game_math.h"
#include <iostream>


Character::Character(SDL_Rect area, SdlTexture& texture, Camera& cam, Stencil& stn, Cursor& cur)
    : area(area), an(texture), cam(cam), stn(stn), cur(cur){
}


void Character::render(){
    std::cout << this->area.x << " - " << this->area.y << std::endl;
    SDL_Rect dst = {this->area.x - this->cam.getPosX() - this->area.w/2, this->area.y - this->cam.getPosY() - this->area.h/2, this->area.w, this->area.h};
    this->an.render(dst, this->cur.getDegrees());
    this->stn.render(this->cam.getPosX(), this->cam.getPosY(), this->cur.getDegrees());
}


void Character::lookAt(int x, int y, int relX, int relY){
    // se le resta la pos de la camara para que resulte la psicion del jguador
    // en la screen y no del nivel.
    this->cur.lookAt(this->area.x - this->cam.getPosX(), this->area.y - this->cam.getPosY(), x, y, relX, relY);
}

int metersToPixel(float pos, int level_meters, int level_pixs){
    int porcentage = (pos*100.0)/ (double)level_meters;
    
    return (level_pixs*porcentage)/100;
}

void Character::update(const ModelInfo model, const LevelInfo level) {

    int x = metersToPixel(model.you.x, level.w_meters, level.width);
    int y = metersToPixel(model.you.y, level.h_meters, level.height);

    

    // para que cambia de frame solo si avanza
    if (this->area.x != x || this->area.y != y) {

        this->an.advanceFrame();
    }
    this->area.x = x;
    this->area.y = y;
    
    this->cam.centerCamera(this->getRect());
    this->cam.keepInBounds(level.width, level.height);
    this->stn.setStencil(this->getRect());
}

int Character::getPosY(){return this->area.y;}
int Character::getPosX(){return this->area.x;}
SDL_Rect Character::getRect(){return this->area;}
