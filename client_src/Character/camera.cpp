#include "camera.h"

Camera::Camera(int width, int height){
    this->camera = {0, 0, width, height};
}

void Camera::centerCamera(SDL_Rect character){
    this->camera.x = character.x - this->camera.w / 2;
    this->camera.y = character.y - this->camera.h / 2;
}

void Camera::centerCameraOnMouse(int tile_width, int level_width, int level_height){
	//Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Move camera to the left if needed
    if(x < tile_width){
        camera.x -= 20;
    }
    
    //Move camera to the right if needed
    if(x > camera.w - tile_width){
        camera.x += 20;
    }
    
    //Move camera up if needed
    if(y < tile_width){
        camera.y -= 20;
    }
    
    //Move camera down if needed
    if(y > this->camera.h - tile_width){
        camera.y += 20;
    }
    
    keepInBounds(level_width, level_height);
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
