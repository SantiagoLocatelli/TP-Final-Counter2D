#include "draggable.h"
#include <stdio.h>

Draggable::Draggable(SdlRenderer& renderer, std::string path, int x, int y) : SdlTexture(renderer, path){
    this->posX = x;
    this->posY = y;
    this->leftMouseButtonDown = false;
    this->selected = false;
}

Draggable::Draggable(SdlRenderer& renderer, std::string path, int x, int y, Uint8 red, Uint8 green, Uint8 blue) : SdlTexture(renderer, path, red, green, blue){
    this->posX = x;
    this->posY = y;
    this->leftMouseButtonDown = false;
    this->selected = false;
}


void Draggable::handleEvent(SDL_Event* event, SDL_Rect camera){
    switch (event->type){
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&this->mousePos.x, &this->mousePos.y);
            if (this->leftMouseButtonDown && this->selected){
                this->posY = this->mousePos.y + camera.y - clickOffset.y;
                this->posX = this->mousePos.x + camera.x - clickOffset.x;
            }
            break;
        
        case SDL_MOUSEBUTTONUP:
            if (this->leftMouseButtonDown && event->button.button == SDL_BUTTON_LEFT){
                this->leftMouseButtonDown = false;
                this->selected = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (!this->leftMouseButtonDown && event->button.button == SDL_BUTTON_LEFT){
                this->leftMouseButtonDown = true;
                if (isToching(camera)){
                    this->selected = true;
                    clickOffset.x = this->mousePos.x + camera.x - this->posX;
                    clickOffset.y = this->mousePos.y + camera.y - this->posY;
                    
                    break;
                }
            }
            break;
    }
}

bool Draggable::isToching(SDL_Rect camera){
    
    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (this->mousePos.x + camera.x < this->posX){
        inside = false;
    }
    //Mouse is right of the button
    else if (this->mousePos.x + camera.x > this->posX + SdlTexture::getWidth()){
        inside = false;
    }
    //Mouse above the button
    else if (this->mousePos.y + camera.y < this->posY){
        inside = false;
    }
    //Mouse below the button
    else if (this->mousePos.y + camera.y > this->posY + SdlTexture::getHeight()){
        inside = false;
    }

    return inside;
}

void Draggable::render(int width, int height){
    SdlTexture::render(this->posX, this->posY, width, height);
}

void Draggable::render(SDL_Rect camera){
    SdlTexture::render(posX - camera.x, posY - camera.y);
}

int Draggable::getPosX(){
    return this->posX;
}

int Draggable::getPosY(){
    return this->posY;
}

SDL_Rect Draggable::getBox(){
    return {posX, posY, SdlTexture::getWidth(), SdlTexture::getHeight()};
}