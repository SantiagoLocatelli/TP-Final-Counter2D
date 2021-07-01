#include "button.h"
#include <utility>

SdlButton::SdlButton(SdlTexture* texture, int x, int y){
	this->mPosition.x = x;
	this->mPosition.y = y;
    this->mCurrentSprite = texture;
    //this->textures = texture;
}

void SdlButton::setPosition(int x, int y){
	this->mPosition.x = x;
	this->mPosition.y = y;
}

void SdlButton::handleEvent(SDL_Event* e){
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < this->mPosition.x){
            inside = false;
        }
        //Mouse is right of the button
        else if (x > this->mPosition.x + this->mCurrentSprite->getWidth()){
            inside = false;
        }
        //Mouse above the button
        else if (y < this->mPosition.y){
            inside = false;
        }
        //Mouse below the button
        else if (y > this->mPosition.y + this->mCurrentSprite->getHeight()){
            inside = false;
        }

        //Mouse is outside button
        if (!inside){
            this->mCurrentSprite->setColor(255, 255, 255);
        }
        //Mouse is inside button
        else{
            //Set mouse over sprite
            switch (e->type){
                case SDL_MOUSEMOTION:
                this->mCurrentSprite->setColor(255, 255, 0);
                break;
            }
        }
    }
}

void SdlButton::render(){
	//Show current button sprite
	this->mCurrentSprite->render(this->mPosition.x, this->mPosition.y);
}

SdlButton::~SdlButton(){
    this->mCurrentSprite->free();
}