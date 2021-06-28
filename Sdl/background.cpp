#include "background.h"

Background::Background(const SdlTexture& texture, Camera& cam, int level_w, int level_h)
    :bg(texture), cam(cam), level_w(level_w),level_h(level_h){}

void Background::render(){
    SDL_Rect area = this->cam.getRect();
    this->bg.render(0, 0, level_w, level_h, &area);
}
