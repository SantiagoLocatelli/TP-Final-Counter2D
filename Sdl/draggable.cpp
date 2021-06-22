#include "draggable.h"
#include <stdio.h>

Draggable::Draggable(SdlRenderer& renderer, std::string path, int x, int y) : SdlTexture(renderer, path){
    this->posX = x;
    this->posY = y;
    this->leftMouseButtonDown = false;
    this->selected = false;
}

void Draggable::handleEvent(SDL_Event* event){
    switch (event->type){
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&this->mousePos.x, &this->mousePos.y);
        
            if (this->leftMouseButtonDown && this->selected){
                this->posY = this->mousePos.y - clickOffset.y;
                this->posX = this->mousePos.x - clickOffset.x;
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
                if (isToching()){
                    this->selected = true;
                    clickOffset.x = this->mousePos.x - this->posX;
                    clickOffset.y = this->mousePos.y - this->posY;
                    
                    break;
                }
            }
            break;
    }
}

bool Draggable::isToching(){
    
    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (this->mousePos.x < this->posX){
        inside = false;
    }
    //Mouse is right of the button
    else if (this->mousePos.x > this->posX + SdlTexture::getWidth()){
        inside = false;
    }
    //Mouse above the button
    else if (this->mousePos.y < this->posY){
        inside = false;
    }
    //Mouse below the button
    else if (this->mousePos.y > this->posY + SdlTexture::getHeight()){
        inside = false;
    }

    return inside;
}

void Draggable::render(){
    SdlTexture::render(this->posX, this->posY);
}
