#include "wall.h"

Wall::Wall(int x, int y, SdlRenderer& r, std::string path, SDL_Rect clip) : GameObject(x,y,r,path){
    this->clip = clip;
}

void Wall::render(SDL_Rect& camera){
    GameObject::render(camera, this->clip);
}