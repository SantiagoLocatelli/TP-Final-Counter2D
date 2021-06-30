#include "animation.h"

#define FRAME_HORIZONTALES 2
#define FRAME_VERTICALES 3
#define PHASE_SHIFT 90
#define DELAY_ANIMATION 3

Animation::Animation(SdlTexture& texture):
    texture(texture) {
    // esto solo lo hago porque se el formato de la textura
    this->numFrames = (this->texture.getHeight()*2)/(this->texture.getWidth()/2);
    this->size = this->texture.getWidth()/2;
}


void Animation::render(SDL_Rect dst, double degrees){
    /* 
    la animacion se compone de 6 frames.
    2 horizontales * 3 verticales
    */
    int frame_vertical = (this->currentFrame % FRAME_VERTICALES);
    int frame_hori = this->currentFrame % FRAME_HORIZONTALES;
    SDL_Rect src = { frame_hori * this->size, frame_vertical * this->size, this->size, this->size};
    this->texture.render(dst.x, dst.y, dst.w, dst.h, &src, degrees + PHASE_SHIFT);
}

void Animation::advanceFrame(){
    if (this->delay > DELAY_ANIMATION) {
        this->currentFrame++;
        this->currentFrame = this->currentFrame % this->numFrames;
        this->delay = 0;
    } else {
        this->delay++;
    }
}


Animation& Animation::operator=(const Animation& other){ 
    this->numFrames = other.numFrames;
    this->currentFrame = other.currentFrame;
    this->size = other.size;
    this->texture = other.texture;
    return *this;
}
Animation::Animation(Animation&& other):texture(other.texture){
    this->numFrames = other.numFrames;
    this->currentFrame = other.currentFrame;
    this->size = other.size;
}