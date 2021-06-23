#include "animation.h"

#define FRAME_HORIZONTALES 2
#define FRAME_VERTICALES 3

Animation::Animation(const SdlTexture& texture):
    texture(texture) {
    // esto solo lo hago porque se el formato de la textura
    this->numFrames = (this->texture.getHeight()*2)/(this->texture.getWidth()/2);
    this->size = this->texture.getWidth()/2;
}

void Animation::update(float dt){
    // rever el codigo de esto
    this->elapsed += dt;
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

void Animation::render(SDL_Rect dst, double degrees){
    /* 
    la animacion se compone de 6 frames.
    2 horizontales * 3 verticales
    */
    int frame_vertical = (this->currentFrame % FRAME_VERTICALES);
    int frame_hori = this->currentFrame % FRAME_HORIZONTALES;
    SDL_Rect src = { frame_hori * this->size, frame_vertical * this->size, this->size, this->size};
    this->texture.render(dst.x, dst.y, dst.w, dst.h, &src, degrees);
}

void Animation::advanceFrame(){
    this->currentFrame++;
    this->currentFrame = this->currentFrame % this->numFrames;
}
