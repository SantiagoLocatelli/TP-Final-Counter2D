#include "stencil.h"

#define PI 3.14159265
#define OPACITY 150

typedef struct coordenada{
    int x, y;
}coordenada_t;

Stencil::Stencil(SdlTexture& stencil, int screen_w, int screen_h)
    :stencil(stencil) {
    this->rect.w = screen_w;
    this->rect.h = screen_h;
    this->rect.x = 0;
    this->rect.y = 0;
    this->oldPosX = 0;
    this->oldPosY = 0;
}

void Stencil::centerStencil(SDL_Rect character) {
    this->rect.x = ( character.x + character.w / 2);
    this->rect.y = ( character.y + character.h / 2);
}

void Stencil::render(int camX, int camY, double degrees){
    this->stencil.setAlpha(OPACITY);
    this->stencil.render(this->rect.x - this->rect.w - camX, this->rect.y - this->rect.h - camY , this->rect.w*2, this->rect.h*2, NULL, degrees);
}
