#include "stencil.h"

#define OPACITY 150

Stencil::Stencil(SdlTexture& stencil, int level_w, int level_h)
    :stencil(stencil) {
    this->rect.w = level_w;
    this->rect.h = level_h;
    this->rect.x = 0;
    this->rect.y = 0;
}

void Stencil::centerStencil(SDL_Rect character) {
    this->rect.x = ( character.x + character.w / 2);
    this->rect.y = ( character.y + character.h / 2);
}

void Stencil::render(int camX, int camY, double degrees){
    this->stencil.setAlpha(OPACITY);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, degrees);
}

Stencil& Stencil::operator=(const Stencil& other){
    this->rect = other.rect;
    this->stencil = other.stencil;
    return *this;
}
Stencil::Stencil(Stencil&& other):stencil(other.stencil){
    this->rect = other.rect;
}
