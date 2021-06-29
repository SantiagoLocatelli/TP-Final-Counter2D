#include "stencil.h"

#define PI 3.14159265
#define OPACITY 150

typedef struct coordenada{
    int x, y;
}coordenada_t;

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


void Stencil::fillStencil(){
    SDL_Surface *surf;
    int st;
    void *pixels;
    int format  = SDL_PIXELFORMAT_RGBA32;
    pixels  = NULL;
    surf    = NULL;

    SdlRenderer& ren = this->stencil.getRenderer();
    SDL_Texture* target = this->stencil.getRenderTarget();

    SDL_Texture* ren_tex;
    ren_tex = this->stencil.createTexture(this->rect.w, this->rect.h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we 
     * can access
     */
    st = this->stencil.setRenderTarget(ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
    }

    ren.setDrawColor(0x00, 0x00, 0x00, 0x00);
    ren.clear();

    st = this->stencil.render(this->rect.x, this->rect.y, );
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(this->rect.w * this->rect.h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        SDL_FreeSurface(surf);
    }

    st = ren.renderReadPixels(pixels, this->rect.w, format);
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        return;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, this->rect.w, this->rect.h, SDL_BITSPERPIXEL(format), this->rect.w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        return;
    }

    

    ren.setRenderTarget(target);
    /* Save result to an image */
    st = SDL_SaveBMP(surf, "gato");
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        SDL_FreeSurface(surf);
        free(pixels);
        SDL_DestroyTexture(ren_tex);
        return;
    }
}


Stencil& Stencil::operator=(const Stencil& other){
    this->rect = other.rect;
    this->stencil = other.stencil;
    return *this;
}
Stencil::Stencil(Stencil&& other):stencil(other.stencil){
    this->rect = other.rect;
}
