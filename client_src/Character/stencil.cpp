#include "stencil.h"

#define OPACITY 150

Stencil::Stencil(SdlTexture& stencil, int level_w, int level_h)
    :stencil(stencil) {
    this->rect.w = level_w;
    this->rect.h = level_h;
    this->rect.x = 0;
    this->rect.y = 0;
}

void Stencil::setStencil(SDL_Rect character, float degrees) {
    this->rect.x = character.x;
    this->rect.y = character.y;
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
Stencil::Stencil(Stencil&& other):stencil(other.stencil){
    this->rect = other.rect;
}
