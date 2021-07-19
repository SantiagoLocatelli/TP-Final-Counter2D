#include "Camera.h"
#include "SDL2/SDL.h"

Camera::Camera(Size size){
    this->size = size;
    this->pos = {0, 0};
}

void Camera::centerCamera(Coordinate pos){
    this->pos.x = pos.x - this->size.w/2;
    this->pos.y = pos.y - this->size.h/2;
}

void Camera::centerCameraOnMouse(int tile_width, int level_width, int level_height){
	//Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState(&x, &y);
    
    //Move camera to the left if needed
    if(x < tile_width){
        pos.x -= 8;
    }
    
    //Move camera to the right if needed
    if(x > size.w - tile_width){
        pos.x += 8;
    }
    
    //Move camera up if needed
    if(y < tile_width){
        pos.y -= 8;
    }
    
    //Move camera down if needed
    if(y > this->size.h - tile_width){
        pos.y += 8;
    }
    
    keepInBounds(level_width, level_height);
}

void Camera::keepInBounds(int level_width, int level_height){
    if( pos.x < 0 ){ 
        pos.x = 0;
    }
    if( pos.y < 0 ){
        pos.y = 0;
    }
    if( pos.x > level_width - size.w ){
        pos.x = level_width - size.w;
    }
    if( pos.y > level_height - size.h ){
        pos.y = level_height - size.h;
    }
}

Size Camera::getSize(){return this->size;}
int Camera::getWidth(){return this->size.w;}
int Camera::getHeight(){return this->size.h;}
int Camera::getPosX(){return this->pos.x;}
int Camera::getPosY(){return this->pos.y;}

SDL_Rect Camera::getRect(){return {this->pos.x, this->pos.y, this->size.w, this->size.h};}
