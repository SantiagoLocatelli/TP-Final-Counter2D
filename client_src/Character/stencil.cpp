#include "stencil.h"
#include "../Events/gameMath.h"

#define OPACITY 150
#define PATH_STENCIL "../../common_src/img/stencil.bmp"

Stencil::Stencil(SdlRenderer& renderer, int window_w, int window_h)
    :stencil(renderer, "../common_src/img/stencil.bmp") {
    this->rect.w = window_w;
    this->rect.h = window_h;
    this->rect.x = 0;
    this->rect.y = 0;
}

void Stencil::setPosition(Prot_Player player, const LevelInfo level){
    //printf("player: x: %i, y: %i\n", player.x, player.y);
    this->rect.x = Math::ruleOfThree(player.x, level.w_meters, level.width);
    this->rect.y = Math::ruleOfThree(player.y, level.w_meters, level.width);
    this->degrees = Math::radiansToDegrees(player.angle);
}


void Stencil::render(int camX, int camY){
    this->stencil.setAlpha(OPACITY);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, this->degrees);
}

Stencil& Stencil::operator=(Stencil&& other){
    this->rect = other.rect;
    this->stencil = std::move(other.stencil);
    return *this;
}
Stencil::Stencil(Stencil&& other):stencil(std::move(other.stencil)){
    this->rect = other.rect;
}
