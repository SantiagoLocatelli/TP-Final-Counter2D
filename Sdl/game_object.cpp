#include "game_object.h"
GameObject::GameObject(int x, int y, SdlRenderer& r, std::string path) : texture(r, path){
    this->mBox.x = x;
    this->mBox.y = y;

    //Set the collision box
    this->mBox.w = 80;
    this->mBox.h = 80;// tamanio de los tiles harcodeado
}

void GameObject::render(int x, int y){
    this->texture.render(x,y);
}

void GameObject::render(SDL_Rect& camera, SDL_Rect clip){
    //If the tile is on screen
    //if (checkCollision(camera, mBox)){
        //Show the tile
        this->texture.render(mBox.x - camera.x, this->mBox.y - camera.y, &clip);
    //}
}


SDL_Rect GameObject::getBox(){
    return this->mBox;
}