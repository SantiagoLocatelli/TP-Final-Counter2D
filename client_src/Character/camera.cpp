#include "camera.h"

Camera::Camera(int width, int height){
    this->camera = {0, 0, width, height};
}

void Camera::centerCamera(SDL_Rect character){
    this->camera.x = character.x - this->camera.w / 2;
    this->camera.y = character.y - this->camera.h / 2;
}

void Camera::keepInBounds(int level_width, int level_height){
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

int Camera::getWidth(){return this->camera.w;}
int Camera::getHeight(){return this->camera.h;}
int Camera::getPosX(){return this->camera.x;}
int Camera::getPosY(){return this->camera.y;}

SDL_Rect Camera::getRect(){return this->camera;}
