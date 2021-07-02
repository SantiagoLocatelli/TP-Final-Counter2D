#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


Character::Character(int width, int height, SdlTexture& texture)
    : an(texture), degrees(0.0){

    this->area.x = 0;
    this->area.y = 0;
    this->area.w = width;
    this->area.h = height;
}


void Character::render(int camX, int camY){
    //std::cout << this->area.x << " - " << this->area.y << std::endl;
    SDL_Rect dst = {this->area.x - camX - this->area.w/2, this->area.y - camY - this->area.h/2, this->area.w, this->area.h};
    this->an.render(dst, this->degrees);
}


void Character::lookAt(int x, int y, int relX, int relY){
    // se le resta la pos de la camara para que resulte la psicion del jguador
    // en la screen y no del nivel.
    //this->cur.lookAt(this->area.x - this->cam.getPosX(), this->area.y - this->cam.getPosY(), {x, y, relX, relY});
}



void Character::update(const ModelInfo model, const LevelInfo level){
    //TODO: Agregar metodo para convertir entre grados y radianes
    this->degrees = Math::radiansToDegrees(model.you.angle);
    int x = Math::ruleOfThree(model.you.x, level.w_meters, level.width);
    int y = Math::ruleOfThree(model.you.y, level.h_meters, level.height);

    // para que cambia de frame solo si avanza
    if (this->area.x != x || this->area.y != y) {

        this->an.advanceFrame();
    }
    this->area.x = x;
    this->area.y = y;
}


int Character::getPosY(){return this->area.y;}
int Character::getPosX(){return this->area.x;}
SDL_Rect Character::getRect(){return this->area;}

Character& Character::operator=(const Character& other){
    this->area = other.area;
    this->an = other.an;
    this->degrees = other.degrees;
    return *this;
}
Character::Character(Character&& other): 
    an(std::move(other.an)){
    this->area = other.area;
    this->degrees = other.degrees;
}
