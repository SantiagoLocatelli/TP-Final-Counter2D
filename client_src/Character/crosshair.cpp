#include "crosshair.h"

#define NUM_FRAMES 4


CrossHair::CrossHair(int width, int height, SdlTexture texture)
    :texture(std::move(texture)){
    this->area.x = 0;
    this->area.y = 0;
    this->area.w = width;
    this->area.h = height;
}

void CrossHair::setPosition(Coordenada pos){
    //SDL_GetMouseState(&(this->area.x), &(this->area.y));
    this->area.x = pos.x - this->area.w/2;
    this->area.y = pos.y - this->area.h/2;
}

void CrossHair::render(){
    SDL_Rect src = {0, 0, 46, 46}; // para quedarnos solo con el puntero verde
    this->texture.render(this->area.x, this->area.y, this->area.w, this->area.h, &src);
}