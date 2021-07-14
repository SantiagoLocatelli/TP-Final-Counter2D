#include "stencil.h"
#include "../Events/gameMath.h"

#define OPACITY 225
#define PATH_STENCIL "../../common_src/img/stencil.bmp"

Stencil::Stencil(SdlRenderer& renderer, Size size)
    :stencil(renderer, PATH_STENCIL, 0xff, 0xff, 0xff) {

    this->rect.w = size.w;
    this->rect.h = size.h;
    this->rect.x = 0;
    this->rect.y = 0;
}

void Stencil::setPosition(Coordinate pos, float degrees){
    this->rect.x = pos.x;
    this->rect.y = pos.y;
    this->degrees = degrees;
}


void Stencil::render(Coordinate cam){
    this->stencil.setBlendMode(SDL_BLENDMODE_BLEND);
    this->stencil.setAlpha(OPACITY);
    this->stencil.render(this->rect.x - this->rect.w - 50 - cam.x, this->rect.y - 50 - this->rect.h - cam.y , (this->rect.w*2) + 100, (this->rect.h*2) + 100, NULL, this->degrees);
}

Stencil& Stencil::operator=(Stencil&& other){
    this->rect = other.rect;
    this->stencil = std::move(other.stencil);
    return *this;
}
Stencil::Stencil(Stencil&& other):stencil(std::move(other.stencil)){
    this->rect = other.rect;
}
