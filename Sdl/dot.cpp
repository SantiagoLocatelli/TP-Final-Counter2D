#include "dot.h"
#define DOT_VEL 10

Dot::Dot(int posX, int posY, int width, int height){
    this->mPosX = posX;
    this->mPosY = posY;

    this->mVelX = 0;
    this->mVelY = 0;

    this->mWidth = width;
    this->mHeight = height;
}

void Dot::handleEvent( SDL_Event& e ){
    //If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch (e.key.keysym.sym){
            case SDLK_UP: this->mVelY -= DOT_VEL; break;
            case SDLK_DOWN: this->mVelY += DOT_VEL; break;
            case SDLK_LEFT: this->mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: this->mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        //Adjust the velocity
        switch (e.key.keysym.sym){
            case SDLK_UP: this->mVelY += DOT_VEL; break;
            case SDLK_DOWN: this->mVelY -= DOT_VEL; break;
            case SDLK_LEFT: this->mVelX += DOT_VEL; break;
            case SDLK_RIGHT: this->mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(int level_width, int level_height){
    //Move the dot left or right
    this->mPosX += this->mVelX;

    //If the dot went too far to the left or right
    if ((this->mPosX < 0) || (this->mPosX + this->mWidth > level_width));{
        //Move back
        this->mPosX -= this->mVelX;
    }

    //Move the dot up or down
    this->mPosY += this->mVelY;

    //If the dot went too far up or down
    if ((this->mPosY < 0) || (this->mPosY + this->mHeight > level_height)){
        //Move back
        this->mPosY -= this->mVelY;
    }
}
