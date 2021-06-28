#include "background.h"

Background::Background(const SdlTexture& texture, Camera& cam)
    :bg(texture), cam(cam){}

void Background::render(){
    SDL_Rect area = this->cam.getRect();
    this->bg.render(0, 0, &area);
}
