#include "stencil.h"

#define OPACITY 150
#define PATH_STENCIL "../../common_src/img/stencil.bmp"

Stencil::Stencil(SdlRenderer& renderer, int window_w, int window_h)
    :stencil(renderer, PATH_STENCIL) {
    this->rect.w = window_w;
    this->rect.h = window_h;
    this->rect.x = 0;
    this->rect.y = 0;
}

void Stencil::setPosition(int posX, int posY, float degrees) {
    this->rect.x = posX;
    this->rect.y = posY;
    this->degrees = degrees;
}


void Stencil::render(int camX, int camY){
    this->stencil.setAlpha(OPACITY);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, this->degrees);
}

Stencil& Stencil::operator=(const Stencil& other){
    this->rect = other.rect;
    this->stencil = other.stencil;
    return *this;
}
Stencil::Stencil(Stencil&& other):stencil(std::move(other.stencil)){
    this->rect = other.rect;
}
