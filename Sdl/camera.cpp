#include "camera.h"
#include "dot.h"

Camera::Camera(int width, int height, int level_width, int level_height):
    level_width(level_width), level_height(level_height){
    this->camera = {0, 0, width, height};
}

void Camera::centerCamera(SDL_Rect character){
    this->camera.x = ( character.x + character.w / 2 ) - this->camera.w / 2;
    this->camera.y = ( character.y + character.h / 2 ) - this->camera.h / 2;
}
void Camera::keepInBounds(){
    if( camera.x < 0 ){ 
        camera.x = 0;
    }
    if( camera.y < 0 ){
        camera.y = 0;
    }
    if( camera.x > level_width - camera.w ){
        camera.x = level_width - camera.w;
    }
    if( camera.y > level_height - camera.h ){
        camera.y = level_height - camera.h;
    }
}

int Camera::getPosX(){
    return this->camera.x;
}

int Camera::getPosY(){
    return this->camera.y;
}

SDL_Rect* Camera::getRect(){
    return &(this->camera);
}
